#ifndef ROUTING_H_
#define ROUTING_H_
#include<bits/stdc++.h>
#include <omnetpp.h>

using namespace std;

class Routing {
protected:
    Routing();
    static Routing *singleton_;

    int **conn;
    int size;
    vector<vector<string>> adjList;
    map<string, int> switchesMap;
    map<string, int> hostsMap;
    void init();
    int next(int src, int dst);
    void printPath(int src, int dst);
    int next(const char *src, const char *dst);
public:
    Routing(Routing &other) = delete;
    void operator=(const Routing&) = delete;

    static Routing* getInstance();
    map<string, int> getRoutingTable(const char *srcName);
};
#endif /* ROUTING_H_ */
