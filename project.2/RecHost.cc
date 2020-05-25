#include<bits/stdc++.h>
#include <omnetpp.h>

using namespace omnetpp;
using namespace std;

class RecHost: public cSimpleModule {
private:
    double TIMEOUT;
    double INTERVAL;

    int *receivedMsgCount;
    int arrayLength;
    int intervalCount = 0;
    int numReceived = 0;

protected:
    virtual void initialize() override;
    virtual void finish() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(RecHost);

void RecHost::initialize() {
    // Thiết lập hằng số
    TIMEOUT = getParentModule()->par("TIMEOUT").doubleValue();
    INTERVAL = getParentModule()->par("INTERVAL").doubleValue();

    // Khởi tạo mảng lưu kết quả
    arrayLength = TIMEOUT / INTERVAL;
    receivedMsgCount = new int[arrayLength];
    memset(receivedMsgCount, 0, arrayLength * sizeof(int));

    scheduleAt(0, new cMessage("nextInterval"));

}
void RecHost::handleMessage(cMessage *msg) {
    // Kiểm tra TIMEOUT
    if (simTime() >= TIMEOUT) {
        return;
    }

    // Nhận và đếm gói tin
    if (strcmp(msg->getName(), "Msg") == 0) {
        int msgId = msg->par("msgId").longValue();
        EV << "Switch received Msg id = " << msgId << endl;
        receivedMsgCount[intervalCount]++;
        numReceived++;
        delete msg;
    }

    // Chuyển interval
    if (strcmp(msg->getName(), "nextInterval") == 0) {
        intervalCount++;
        scheduleAt(simTime() + INTERVAL, msg);
    }

}

void RecHost::finish() {

    for (int i = 0; i < arrayLength; i++) {
            EV << "Interval " << i <<", " << receivedMsgCount[i]
                          << " message(s)" << " received" << endl;
    }
        EV << "Interval time: " << INTERVAL << " s" << endl;
        EV << "Total interval: " << TIMEOUT / INTERVAL << endl;
        EV << "Total messages received: " << numReceived << endl;
        EV << "Messages received per 1 second " << numReceived/TIMEOUT << endl;
}

