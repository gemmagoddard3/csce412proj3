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
    int nextServer;
    int numServer;

public:
    LoadBalancer(queue<Request *> rq, int numServ);
    void addRequest(Request *req);
    void setNextServer();
    Request *getNextInQueue();
    void processRequests();
};

#endif