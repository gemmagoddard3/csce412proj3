#include "LoadBalancer.h"

LoadBalancer::LoadBalancer(queue<Request *> rq){
    requestQueue = rq;
}

void LoadBalancer::addRequest(Request * req){
    requestQueue.push(req);
}

Request * LoadBalancer::getNextInQueue(){
    Request * ret = requestQueue.front();
    requestQueue.pop();
    return ret;
}