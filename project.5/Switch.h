#ifndef __SWITCH_H__
#define __SWITCH_H__

#include<bits/stdc++.h>
#include <omnetpp.h>
#include "Routing.h"

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

    cModule *neighbors[7]; // mỗi nút đều kết nối với 7 nút khác (6 switch + 1 host)

    queue<cMessage*> ENB[7];
    queue<cMessage*> EXB[7];

    int numSpacesOfNextENB[6]; // 6 biến đếm tương ứng 6 switch đc kết nối.

    map<string, int> routingTable;

    void printRoutingTable();
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;

    int chooseENB(int EXBid); // Gói tin tiếp theo được chuyển sang EXB nằm ở ENB nào?
    void ENBtoEXB(int ENBid, int EXBid); // Chuyển từ ENB sang EXB
    void incNumSpacesOfNextENB(const char *switchName);
};

#endif
