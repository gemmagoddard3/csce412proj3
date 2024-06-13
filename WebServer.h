#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <string>
#include <queue>
#include <chrono>
#include <mutex>
#include "Request.h"
using namespace std;

class WebServer
{
private:
    queue<Request *> serverQueue;
    int serverID;
    mutex mux;

public:
    WebServer(int id);
    void addRequest(Request * req);
    void processRequests();
};

#endif