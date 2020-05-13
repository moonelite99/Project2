#include <string.h>
#include <omnetpp.h>
#include <string>

using namespace omnetpp;

class Switch: public cSimpleModule {
private:
    double TIMEOUT;
    double MSG_GEN_INTERVAL;
    int *receivedMsgCount;
    int arrayLength;
    int intervalCount = 0;
    int msgCount = 1;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
};

Define_Module(Switch);

void Switch::initialize() {
    // Thiết lập các hằng số
    MSG_GEN_INTERVAL = getParentModule()->par("MSG_GEN_INTERVAL").doubleValue();
    TIMEOUT = getParentModule()->par("TIMEOUT").doubleValue();

    // Khởi tạo mảng
    arrayLength = TIMEOUT / MSG_GEN_INTERVAL + 1;
    receivedMsgCount = new int[arrayLength];
    memset(receivedMsgCount, 0, arrayLength * sizeof(int));

    scheduleAt(0, new cMessage("nextInterval"));
}

void Switch::handleMessage(cMessage *msg) {
    // Kiểm tra TIMEOUT
    if (simTime() >= TIMEOUT){
        return;
    }

    // Nhận và đếm số gói tin
    if (strcmp(msg->getName(), "Msg") == 0) {
        EV << "Received Msg " << msgCount << endl;
        msgCount++;
        receivedMsgCount[intervalCount]++;
        delete msg;
    }

    // Chuyển interval
    if (strcmp(msg->getName(), "nextInterval") == 0) {
        intervalCount++;
        scheduleAt(simTime() + MSG_GEN_INTERVAL, msg);
    }
}

void Switch::finish(){
    for (int i = 1; i < arrayLength; i++) {
        if(receivedMsgCount[i] < 2)
            EV << "interval " << i <<", " << receivedMsgCount[i]
                  << " message" << " received" << endl;
        else
            EV << "interval " << i <<", " << receivedMsgCount[i]
                              << " messages" << " received" << endl;
    }
}

