#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <string>
#include <queue>
#include <chrono>
#include <mutex>
#include "Request.h"

class LoadBalancer; 

using namespace std;

class WebServer
{
private:
    queue<Request *> serverQueue;
    int serverID;

public:
    WebServer(int id);
    void addRequest(Request * req);
    void processRequests(LoadBalancer * lb);
    int numInQueue();
    int getId();
};

#endif