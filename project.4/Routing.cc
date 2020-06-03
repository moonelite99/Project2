#include<bits/stdc++.h>
#include <omnetpp.h>

using namespace omnetpp;
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

Routing *Routing::singleton_ = nullptr;

Routing::Routing(){
    init();
}

Routing* Routing::getInstance() {
    if (singleton_ == nullptr) {
        singleton_ = new Routing();
    }
    return singleton_;
}

void Routing::init() {

    /////////////////////////////////////
    // Reading connections list from file

    string line;
    ifstream myfile("./ConnectionsList.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            char buffer[7];
            int i = 0;
            adjList.push_back(*new vector<string>);
            for (auto it = line.begin(); it != line.end(); it++) {
                if (*it != ' ') {
                    buffer[i++] = *it;
                }
                else {
                    string s = string(buffer, i);
                    adjList.back().push_back(s);
                    i = 0;
                }
            }
            string s = string(buffer, i);
            adjList.back().push_back(s);
        }
        myfile.close();
    }

    else cout << "Unable to open file";

    for (auto v : adjList) {
        for (auto s : v) {
            cout << s << " ";
        }
        cout << "\n";
    }

    int k = 0;
    for (auto line : adjList) {
        switchesMap.insert(pair<string, int>(line.front(), k));
        hostsMap.insert(pair<string, int>(line.back(), 1000 + k));
        k++;
    }

    /////////////////////////////////////
    // Init connections matrix

    size = adjList.size();
    conn = new int* [size];

    for (int i = 0; i < adjList.size(); i++) {
        conn[i] = new int[7];
        for (int j = 0; j < 6; j++) {
            conn[i][j] = switchesMap.at(adjList[i][j + 1]);
        }
        conn[i][6] = hostsMap.at(adjList[i][7]);
    }

    for (int i = 0; i < adjList.size(); i++) {
        for (int j = 0; j < 7; j++) {
            cout << conn[i][j] << " ";
        }
        cout << endl;
    }
}

/**
 * src: id của switch gửi
 * dst: id của switch nhận
 * return: cổng ra
 */
int Routing::next(int src, int dst) {
    if (src == dst) {
        return -1;
    }
    bool* visited = new bool[size] {false};
    queue<list<pair<int, int>>> myqueue;
    for (int i = 0; i < 6; i++) {
        list<pair<int, int>> l1;
        l1.push_back(pair<int, int>(conn[src][i], i));
        myqueue.push(l1);
    }
    visited[src] = true;
    while (!myqueue.empty()) {
        list<pair<int, int>> l1 = myqueue.front();
        myqueue.pop();
        int hop = l1.back().first;
        if (hop == dst) {
            return l1.front().second;
        }
        for (int i = 0; i < 6; i++) {
            if (!visited[conn[hop][i]]) {
                list<pair<int, int>> l2(l1);
                l2.push_back(pair<int, int>(conn[hop][i], i));
                myqueue.push(l2);
            }
        }
        visited[hop] = true;
    }
    return -2;
}

void Routing::printPath(int src, int dst) {
    cout << "path from " << src << " to " << dst << endl;
    int nextPort = next(src, dst);
    while (nextPort != -1) {
        printf_s("(%d,%d)->", src, nextPort);
        src = conn[src][nextPort];
        nextPort = next(src, dst);
    }
    cout << dst;
}

/**
 * srcName: tên nút gửi (có thể là switch hoặc host)
 * dstName: tên nút nhận (có thể là switch hoặc host)
 * return: Cổng ra
 */
int Routing::next(const char *srcName, const char *dstName) {
    int srcId = -1;
    int dstId = -1;
    if (hostsMap.find(string(srcName)) != hostsMap.end()) {
        return 0;
    }
    srcId = switchesMap.at(string(srcName));

    if (hostsMap.find(string(dstName)) != hostsMap.end()) {
        dstId = hostsMap.at(string(dstName));
        if (conn[srcId][6] == dstId) {
            return 6;
        }
        for (int i = 0; i < 27; i++) {
            if (conn[i][6] == dstId) {
                return next(srcId, i);
            }
        }
        return -1;
    }

    dstId = switchesMap.at(string(dstName));
    return next(srcId, dstId);
}

/**
 * srcName: tên switch gửi
 * return: bảng định tuyến, ví dụ:
 * h0_0_0 | 3
 * h0_0_1 | 2
 * h0_0_2 | 3
 * h0_1_0 | 0
 * h0_1_1 | 0
 * h0_1_2 | 0
 * h0_2_0 | 4
 * h0_2_1 | 2
 * h0_2_2 | 4
 * h1_0_0 | 1
 * h1_0_1 | 1
 * h1_0_2 | 1
 * h1_1_0 | 0
 * h1_1_1 | 0
 * h1_1_2 | 0
 * h1_2_0 | 1
 * h1_2_1 | 1
 * h1_2_2 | 1
 * h2_0_0 | 3
 * h2_0_1 | 2
 * h2_0_2 | 3
 * h2_1_0 | 0
 * h2_1_1 | 0
 * h2_1_2 | 0
 * h2_2_0 | 5
 * h2_2_1 | 2
 * h2_2_2 | 6
 */
map<string, int> Routing::getRoutingTable(const char *srcName) {
    map<string, int> routingTable;
    for (int i = 0; i < 27; i++) {
        routingTable.insert(pair<string, int>(adjList[i][7], next(srcName, adjList[i][7].c_str())));
    }
    return routingTable;
}
