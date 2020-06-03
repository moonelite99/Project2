#include<bits/stdc++.h>
#include <omnetpp.h>
#include"Routing.h"
using namespace omnetpp;
using namespace std;

class Switch: public cSimpleModule {
private:
    map<string, int> routingTable;

    void printRoutingTable();
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Switch);

void Switch::initialize() {
    Routing* r = Routing::getInstance();
    routingTable = r->getRoutingTable(getName());
    printRoutingTable();
}

void Switch::handleMessage(cMessage *msg) {
    string dstName = string(msg->par("dst").stringValue());
    EV << "switch " << getName() << endl;
    EV << "dstName = " << dstName << endl;
    int portOut = routingTable.at(dstName);
    EV << "portOut = " << portOut;
    send(msg, "port$o", portOut);
}

void Switch::printRoutingTable() {
    EV << "Routing table at " << getName() << " :" << endl;
    for (auto it = routingTable.begin(); it != routingTable.end(); it++) {
        EV << it->first << " | " << it->second << endl;
    }
}
