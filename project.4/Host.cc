#include<bits/stdc++.h>
#include <omnetpp.h>

using namespace omnetpp;
using namespace std;

class Host: public cSimpleModule {
private:

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Host);

void Host::initialize() {
    if (strcmp(getName(), "h0_0_0") == 0) {
        cMessage *testMsg = new cMessage("Msg");
        cMsgPar *msgPar = new cMsgPar("dst");
        msgPar->setStringValue("h1_1_1");
        testMsg->addPar(msgPar);
        send(testMsg, "port$o", 0);
    }
}

void Host::handleMessage(cMessage *msg) {
    string dstName = msg->par("dst").stringValue();
    if (dstName.compare(getName()) == 0) {
        bubble("received Msg");
    }
}
