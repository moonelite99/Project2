#include<bits/stdc++.h>
#include <omnetpp.h>

using namespace omnetpp;
using namespace std;

class Switch: public cSimpleModule {
private:
    double TIMEOUT;
    double CREDIT_DELAY;
    double OPERATION_TIME_PERIOD;
    double CHANNEL_DELAY;

    int ENB_SIZE;
    int EXB_SIZE;

    int busy = 0;

    cModule *hosts[3];

    queue<cMessage*> ENB[3]; // Entrance Buffer
    queue<cMessage*> EXB; // Exit Buffer

    void forwardMessage(cMessage *msg);
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

    int chooseENB(); // Gói tin tiếp theo được chuyển sang EXB nằm ở ENB nào?
    void ENBtoEXB(int ENBid); // Chuyển từ ENB sang EXB
};

Define_Module(Switch);

void Switch::initialize() {
    // Thiết lập các hằng số

    CHANNEL_DELAY = getParentModule()->par("CHANNEL_DELAY").doubleValue();
    TIMEOUT = getParentModule()->par("TIMEOUT").doubleValue();
    CREDIT_DELAY = getParentModule()->par("CREDIT_DELAY").doubleValue();
    OPERATION_TIME_PERIOD = par("OPERATION_TIME_PERIOD").doubleValue();
    ENB_SIZE = par("ENB_SIZE").intValue();
    EXB_SIZE = par("EXB_SIZE").intValue();

    // Khởi tạo danh sách hosts
    hosts[0] = getParentModule()->getModuleByPath(".A");
    hosts[1] = getParentModule()->getModuleByPath(".B");
    hosts[2] = getParentModule()->getModuleByPath(".C");

    scheduleAt(0, new cMessage("nextPeriod"));
    scheduleAt(0, new cMessage("sendToHost"));
}

void Switch::handleMessage(cMessage *msg) {
    // Kiểm tra TIMEOUT
    if (simTime() >= TIMEOUT) {
        return;
    }

    const char *event = msg->getName();

    //Nếu đường truyền rảnh
    if(strcmp(event, "free") == 0){
        busy = 0;
    }
    // Nhận và đếm số gói tin
    if (strcmp(event, "Msg") == 0) {
        int ENBid = msg->getArrivalGate()->getIndex();
        int msgId = msg->par("msgId").longValue();
        EV << "Switch received Msg id = " << msgId << " at port" << ENBid << endl;
        ENB[ENBid].push(msg);
    }

    // Chu kỳ hoạt động của switch
    if (strcmp(event, "nextPeriod") == 0) {
        // ENB -> EXB
        if (EXB.size() < EXB_SIZE) {
            int ENBid = chooseENB();
            if (ENBid != -1) {
                ENBtoEXB(ENBid);
                // Báo lại
                cMessage *notifMsg = new cMessage("incNumSpaces");
                sendDirect(notifMsg, CREDIT_DELAY, 0, hosts[ENBid], "in");
            }
        }

        scheduleAt(simTime() + OPERATION_TIME_PERIOD, msg);
    }
    if (strcmp(event, "sendToHost") == 0){
        // Nếu đường truyền đang bận
        if(busy == 1){
            scheduleAt(simTime() + OPERATION_TIME_PERIOD, msg);
            return;
            }
        // EXB -> next hop
        else if (!EXB.empty()){
                cMessage *sentMsg = EXB.front();
                EXB.pop();
                forwardMessage(sentMsg);
                busy = 1;
            }
        scheduleAt(simTime() + OPERATION_TIME_PERIOD, msg);
    }
}
int Switch::chooseENB() {
    int minMsgId = INT32_MAX;
    int ENBid = -1;
    for (int i = 0; i < 3; i++) {
        if (!ENB[i].empty()) {
            int msgId = ENB[i].front()->par("msgId").longValue();
            if (msgId < minMsgId) {
                minMsgId = msgId;
                ENBid = i;
            }
        }
    }
    return ENBid;
}

void Switch::ENBtoEXB(int ENBid) {
    if (ENB[ENBid].empty())
        return;
    cMessage* msg = ENB[ENBid].front();
    ENB[ENBid].pop();
    EXB.push(msg);

}

void Switch::forwardMessage(cMessage *msg){
    send(msg, "out");
}

