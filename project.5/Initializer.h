#ifndef INITIALIZER_H_
#define INITIALIZER_H_

#include<bits/stdc++.h>
#include <omnetpp.h>

using namespace omnetpp;
using namespace std;

class Initializer {
protected:
    Initializer();
    static Initializer *singleton_;

    const int N = 4;
    unsigned seed;
    vector<string> hostNames;
public:
    Initializer(Initializer &other) = delete;
    void operator=(const Initializer&) = delete;

    static Initializer* getInstance();

    bool getDuty(string hostName);
    string getPairHostName(string hostName);
};
#endif
