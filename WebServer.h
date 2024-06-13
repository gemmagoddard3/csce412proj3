#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <string>
#include <queue>
#include "Request.h"
using namespace std;

class WebServer
{
private:
    queue<Request *> workerQueue;
public:
    void addRequest(Request * req);
};

#endif