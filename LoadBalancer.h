#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <string>
#include <queue>
#include "Request.h"
#include "WebServer.h"

using namespace std;

class LoadBalancer
{
private:
    queue<Request *> requestQueue;
    vector<WebServer *> webServers;
    vector<bool> serverStatus;
    int numServer;
    int time;
    int endTime;

public:
    LoadBalancer(queue<Request *> rq, vector<WebServer *> ws, vector<bool> ss, int et);
    void addRequest(Request *req);
    int getNextServer();
    Request *getNextInQueue();
    void processRequests();
    int getTime();
    int getEndTime();
    void increaseTime();
};

#endif