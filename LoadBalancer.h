#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <string>
#include <queue>
#include "Request.h"

using namespace std;

class LoadBalancer
{
private:
    queue<Request *> requestQueue;

public:
    LoadBalancer(queue<Request *> rq);
    void addRequest(Request * req);
    Request * getNextInQueue();
};

#endif