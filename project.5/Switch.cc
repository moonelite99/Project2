#include<bits/stdc++.h>
#include <omnetpp.h>

using namespace omnetpp;
using namespace std;
#include "Routing.h"
#include "Switch.h"
#include "Host.h"

Define_Module(Switch);

void Switch::initialize() {
    Routing* routingInstance = Routing::getInstance();
    routingTable = routingInstance->getRoutingTable(getName());
    printRoutingTable();

    // Thiết lập các hằng số

    TIMEOUT = getParentModule()->par("TIMEOUT").doubleValue();
    CREDIT_DELAY = getParentModule()->par("CREDIT_DELAY").doubleValue();
    CHANNEL_DELAY = 0.0001;
    OPERATION_TIME_PERIOD = par("OPERATION_TIME_PERIOD").doubleValue();
    ENB_SIZE = par("ENB_SIZE").intValue();
    EXB_SIZE = par("EXB_SIZE").intValue();

    // Khởi tạo danh sách neighbors
    vector<vector<string>> adjList = routingInstance->getAdjList();
    int t = -1;
    for (t = 0; t < adjList.size(); t++) {
        if (adjList[t][0].compare(string(getName())) == 0) {
            break;
        }
    }
    if (t == -1) {
        throw "Not found this module name in list";
    }
    for (int i = 0; i < 7; i++) {
        neighbors[i] = getParentModule()->getModuleByPath((string(".") + adjList[t][i+1]).c_str());
    }

    // Khởi tạo mảng counter
    for (int i = 0; i < 6; i++) {
        numSpacesOfNextENB[i] = ENB_SIZE;
    }


    // Bắt đầu
    scheduleAt(0, new cMessage("nextPeriod"));
    scheduleAt(0, new cMessage("send"));
}

void Switch::handleMessage(cMessage *msg) {
    // Kiểm tra TIMEOUT
    if (simTime() >= TIMEOUT) {
        delete msg;
        return;
    }

    const char *event = msg->getName();

    // Nhận gói tin vào các ENB
    if (strcmp(event, "testMsg") == 0) {
        int ENBid = msg->getArrivalGate()->getIndex();
        int msgId = msg->par("msgId").longValue();
        EV << "Switch received testMsg id = " << msgId << " at port" << ENBid << endl;
        ENB[ENBid].push(msg);
        return;
    }

    // Chuyển từ ENB sang EXB
    if (strcmp(event, "ENBtoEXB") == 0) {
        int ENBid = msg->par("ENBid").longValue();
        int EXBid = msg->par("EXBid").longValue();
        ENBtoEXB(ENBid, EXBid);
        delete msg;

        // Sau 1 khoảng thời gian thì báo lại cho hop trước
        cMessage *notifMsg = new cMessage("incNumSpaces");
        notifMsg->addPar("ENBid").setLongValue(ENBid);
        scheduleAt(simTime() + CREDIT_DELAY, notifMsg);
        return;
    }

    // Báo lại cho hop trước
    if (strcmp(event, "incNumSpaces") == 0) {
        int ENBid = msg->par("ENBid").longValue();

        cModule *prevHop = neighbors[ENBid];
        if (strcmp(prevHop->getClassName(), "Host") == 0) {
            Host *sendingHost = check_and_cast<Host*>(neighbors[ENBid]);
            sendingHost->incNumSpacesOfNextENB();
        } else if (strcmp(prevHop->getClassName(), "Switch") == 0) {
            Switch *sendingSwitch = check_and_cast<Switch*>(neighbors[ENBid]);
            sendingSwitch->incNumSpacesOfNextENB(getName());
        } else {
            throw "previous hop invalid";
        }

        delete msg;
        return;
    }

    // EXB -> next hop
    if (strcmp(event, "send") == 0) {
        for (int i = 0; i < 7; i++) {
            if (i < 6 && numSpacesOfNextENB[i] <= 0) {
                continue;
            }
            if (!EXB[i].empty()) {
                cMessage *sentMsg = EXB[i].front();
                EXB[i].pop();
                send(sentMsg, "port$o", i);
            }
        }
        scheduleAt(simTime() + CHANNEL_DELAY, msg);
        //scheduleAt(gate("port$o", 0)->getTransmissionChannel()->getTransmissionFinishTime(), msg);
        return;
    }

    // Chu kỳ hđ của switch
    if (strcmp(event, "nextPeriod") == 0){
        for (int i = 0; i < 7; i++) {
            if (EXB[i].size() < EXB_SIZE) {
                // Chọn ra gói tin sẽ được gửi từ ENB sang EXB
                int ENBid = chooseENB(i);
                if (ENBid != -1) {
                    // Ghi lại ENBid vào event và sau 1 chu kỳ thì chuyển gói tin từ ENB đó sang EXB
                    cMessage *enb2exbNotif = new cMessage("ENBtoEXB");
                    enb2exbNotif->addPar("ENBid");
                    enb2exbNotif->addPar("EXBid");
                    enb2exbNotif->par("ENBid").setLongValue(ENBid);
                    enb2exbNotif->par("EXBid").setLongValue(i);
                    scheduleAt(simTime() + OPERATION_TIME_PERIOD, enb2exbNotif);
                }
            }
        }
        scheduleAt(simTime() + OPERATION_TIME_PERIOD, msg);
        return;
    }
}

void Switch::finish() {

}

/**
 * In ra bảng định tuyến
 */
void Switch::printRoutingTable() {
    EV << "Routing table at " << getName() << " :" << endl;
    for (auto it = routingTable.begin(); it != routingTable.end(); it++) {
        EV << it->first << " | " << it->second << endl;
    }
}

/**
 * Chọn ra ENB có gói tin được ưu tiên chuyển tiếp sang EXB tương ứng
 * Quy luật: chọn gói tin có id nhỏ nhất
 * EXBid: index của EXB mà gói tin muốn đi sang
 * return: index của ENB đc chọn
 */
int Switch::chooseENB(int EXBid) {
    int minMsgId = INT32_MAX;
    int ENBid = -1;
    for (int i = 0; i < 7; i++) {
        if (!ENB[i].empty()) {
            cMessage *msg = ENB[i].front();
            string dstName = string(msg->par("dst").stringValue());
            int portOut = routingTable.at(dstName);
            if (portOut == EXBid) {
                int msgId = msg->par("msgId").longValue();
                if (msgId < minMsgId) {
                    minMsgId = msgId;
                    ENBid = i;
                }
            }
        }
    }
    return ENBid;
}

/**
 * Chuyển gói tin từ ENB sang EXB
 */
void Switch::ENBtoEXB(int ENBid, int EXBid) {
    if (ENB[ENBid].empty())
        return;
    cMessage* msg = ENB[ENBid].front();
    ENB[ENBid].pop();
    EXB[EXBid].push(msg);
}

/**
 * Tăng biến đếm số chỗ trống của ENB của switch kế tiếp
 */
void Switch::incNumSpacesOfNextENB(const char* switchName) {
    vector<vector<string>> adjList = Routing::getInstance()->getAdjList();
    int t = -1;
    for (t = 0; t < adjList.size(); t++) {
        if (adjList[t][0].compare(string(getName())) == 0) {
            break;
        }
    }
    if (t == -1) {
        throw "Not found this module name in list";
    }
    for (int i = 0; i < 6; i++) {
        if (adjList[t][i+1].compare(switchName) == 0) {
            numSpacesOfNextENB[i]++;
            EV << "numSp " << i << " = " << numSpacesOfNextENB[i];
            break;
        }
    }
}
