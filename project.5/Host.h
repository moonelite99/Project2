#ifndef __HOST_H__
#define __HOST_H__

#include<bits/stdc++.h>
#include <omnetpp.h>

using namespace omnetpp;
using namespace std;

class Host: public cSimpleModule {
private:
    // constant
    int EXB_SIZE;
    double TIMEOUT;
    double MSG_GEN_TIME_PERIOD;
    double CHANNEL_DELAY;
    double INTERVAL;

    bool isSender;
    string pairHostName;

    int lastestMsgId = -1;

    int *receivedMsgCount;
    int numInterval;
    int interval = 0;

    static int *recvMsgCountSum;

    // source queue
    queue<int> SQ;

    // exit buffer
    queue<int> EXB;

    // số chỗ trống của ENB của switch
    int numSpacesOfNextENB;

    void generateMessage();
    void SQtoEXB(); // Chuyển gói tin từ SQ sang EXB
    void sendMsg(); // Gửi từ EXB đi sang nút khác

protected:
    virtual void initialize() override;
    virtual void finish() override;
    virtual void handleMessage(cMessage *msg) override;

public:
    void incNumSpacesOfNextENB();
};

#endif
