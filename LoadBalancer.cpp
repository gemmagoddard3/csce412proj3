#include "LoadBalancer.h"
#include <string>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "Request.h"
#include "LoadBalancer.h"
#include <queue>
#include <thread>

int LOAD = 50;

LoadBalancer::LoadBalancer(queue<Request *> rq, vector<WebServer *> ws, vector<bool> ss, int et)
{
    requestQueue = rq; // queue of all reques
    webServers = ws;   // vector of the web servers
    serverStatus = ss; // vector of each server status
    time = 0;          // keeping track of time
    endTime = et;
    bool done = false;
}

void LoadBalancer::addRequest(Request *req) // adds a request to the queue
{
    cout << "Adding " << req->getIpIn() << " to the request queue" << endl;
    requestQueue.push(req);
}

Request *LoadBalancer::getNextInQueue() // returns next in queue (if any)
{
    if (!requestQueue.empty())
    {
        Request *ret = requestQueue.front();
        requestQueue.pop();
        return ret;
    }
    else
    {
        return nullptr;
    }
}

void LoadBalancer::getActiveServers(){
    cout << "Active Servers ";
    for(int i = 0; i < serverStatus.size(); i++){
        if(serverStatus.at(i)){
            cout << webServers.at(i)->getId() << " ";
        }
    }
    cout << endl;
}

int LoadBalancer::getNextServer() // getting which server to add next request to
{
    int minServerIndex = 0;
    int minLoad = LOAD * 0.30;

    for (int i = 0; i < webServers.size(); i++)
    {
        // turn off servers that have low usage (below 10% of the load size)
        if(serverStatus.at(i) && webServers.at(i)->numInQueue()< minLoad){
            cout << "Turning off server " << webServers.at(i)->getId() << endl;
            serverStatus.at(i) = false;
            getActiveServers();
        }
    }
 
    // check if there is a running server already that we can send the request to that wont be too much
    for (int i = 0; i < webServers.size(); i++)
    {
        // if there is a current web server allocated that can maintain the load, add it to that
        if (serverStatus.at(i) && (webServers.at(i)->numInQueue() < LOAD))
        {
            return i;
        }

        // finding the web server with smallest num in queue
        if (webServers.at(i)->numInQueue() < webServers.at(minServerIndex)->numInQueue())
        {
            minServerIndex = i;
        }
    }

    // we need to allocate a new server to help the load
    for (int i = 0; i < webServers.size(); i++)
    {
        // if we find a server that isnt running, make it active and send the request there
        if (!serverStatus.at(i))
        {
            // cout << "Turning on server " << webServers.at(i)->getId() << endl;
            serverStatus.at(i) = true;
            return i;
        }
    }

    // if all are full and above the load, assign to the server with the smallest number of requests
    return minServerIndex;
}

void LoadBalancer::processRequests()
{
    while (time < endTime)
    {
        
        if (!requestQueue.empty())
        {
            Request *req = requestQueue.front();
            requestQueue.pop();
            int nextServer = getNextServer();
            webServers.at(nextServer)->addRequest(req);
        }
        this_thread::sleep_for(chrono::milliseconds(2));
        increaseTime();
    }
    done = true;
}

int LoadBalancer::getTime()
{
    return time;
}

bool LoadBalancer::isDone(){
    return done;
}

void LoadBalancer::increaseTime()
{
    time++;
}

int LoadBalancer::getEndTime(){
    return endTime;
}

int LoadBalancer::getRequestCount(){
    int count = 0;
    for(int i = 0; i < webServers.size(); i++){
        count += webServers.at(i)->numInQueue();
    }
    return count;
}

vector<bool> LoadBalancer::getStatus(){
    return serverStatus;
}