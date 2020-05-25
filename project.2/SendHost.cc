#include<bits/stdc++.h>
#include <omnetpp.h>

using namespace omnetpp;
using namespace std;

class SendHost: public cSimpleModule {
private:
    int EXB_SIZE;
    double TIMEOUT;
    double MSG_GEN_TIME_PERIOD;
    double CHANNEL_DELAY;
    // số chỗ trống của ENB của switch
    int numSpacesOfNextENB;
    int lastestMsgId = 0;

    queue<int> SQ;
    queue<int> EXB;

    void generateMessage();
    void SQtoEXB(); // Chuyển gói tin từ SQ sang EXB
    void sendMsg(); // Gửi từ EXB đi sang nút khác
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(SendHost);

void SendHost::initialize(){
        MSG_GEN_TIME_PERIOD = getParentModule()->par("MSG_GEN_TIME_PERIOD").doubleValue();
        TIMEOUT = getParentModule()->par("TIMEOUT").doubleValue();
        EXB_SIZE = par("EXB_SIZE").intValue();
        CHANNEL_DELAY = getParentModule()->par("CHANNEL_DELAY").doubleValue();

        numSpacesOfNextENB = getParentModule()->getModuleByPath(".D")->par("ENB_SIZE").intValue();

        // Bắt đầu quá trình tạo các gói tin
        scheduleAt(0, new cMessage("generate"));
        // Bắt đầu quá trình gửi các gói tin
        scheduleAt(0, new cMessage("send"));
}

void SendHost::handleMessage(cMessage *msg) {
    // Kiểm tra TIMEOUT
    if (simTime() >= TIMEOUT) {
        return;
    }

    // Hoạt động của Source Queue
    // Tạo tin nhắn theo chu kỳ
    if (strcmp(msg->getName(), "generate") == 0) {
        generateMessage();
        // Nếu EXB còn chỗ thì chuyển sang luôn
        if (EXB.size() < EXB_SIZE) {
            SQtoEXB();
        }

        scheduleAt(simTime() + MSG_GEN_TIME_PERIOD, msg);

    }

    // Hoạt động của Exit Buffer
    // Gửi tin nhắn theo chu kỳ

    if (strcmp(msg->getName(), "send") == 0) {
        if(numSpacesOfNextENB > 0){
            sendMsg();
            // Giảm số chỗ trống của ENB kế tiếp đi 1
            numSpacesOfNextENB--;
            SQtoEXB();
        }

        scheduleAt(simTime() + CHANNEL_DELAY, msg);
    }

    // Tin báo tăng từ switch kế
    if (strcmp(msg->getName(), "incNumSpaces") == 0) {
        numSpacesOfNextENB++;
        delete msg;
    }
}
void SendHost::generateMessage() {
    SQ.push(lastestMsgId);
    EV << "Message " << lastestMsgId << " generated" << endl;
    lastestMsgId++;
}

void SendHost::SQtoEXB(){
    if (!SQ.empty()){
        int msgId = SQ.front();
        SQ.pop();
        EXB.push(msgId);
    }
}
void SendHost::sendMsg() {
    if (!EXB.empty() && numSpacesOfNextENB > 0) {
        // Lấy ra id gói tin chuẩn bị gửi
        int sentMsgId = EXB.front();
        EXB.pop();

        // Tạo gói tin
        cMessage *sentMsg = new cMessage("Msg");

        // Gắn id cho gói tin
        cMsgPar *msgParam = new cMsgPar("msgId");
        msgParam->setLongValue(sentMsgId);
        sentMsg->addPar(msgParam);

        // Gửi
        send(sentMsg, "out");
    }
}
