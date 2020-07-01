#ifndef ROUTING_H_
#define ROUTING_H_

#include<bits/stdc++.h>
#include <omnetpp.h>
using namespace std;
class Routing {
protected:
    Routing();
    static Routing *singleton_;

    // Kích thước của mạng Torus3D
    int N = 4;

    // Ma trận kết nối
    int **conn;
    int size;

    // Danh sách kề
    vector<vector<string>> adjList;

    // Map từ tên sang số hiệu
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

    vector<vector<string>> getAdjList();

    map<string, int> getRoutingTable(const char *srcName);

};
#endif /* ROUTING_H_ */
