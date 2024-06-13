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

LoadBalancer::LoadBalancer(queue<Request *> rq, int numServ)
{
    requestQueue = rq;
    numServer = numServ;
    nextServer = 1;

    for (int i = 0; i < numServer; i++)
    {
        webServers.push_back(new WebServer(i + 1));
    }

    for (int i = 0; i < numServer; i++)
    {
        thread serverThread(&WebServer::processRequests, webServers[i]);
        serverThread.detach(); // Detach thread to run independently
    }

    thread addRequestThread(&LoadBalancer::randomlyAddRequest, this);
    addRequestThread.detach(); // Detach the thread to run independently
}

void LoadBalancer::addRequest(Request *req){
    cout << "Adding " << req->getIpIn() << " to the Queue" << endl;
    requestQueue.push(req);
    processRequests();
}

Request *LoadBalancer::getNextInQueue()
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

void LoadBalancer::setNextServer()
{
    nextServer = (nextServer + 1) % numServer;
}

void LoadBalancer::processRequests()
{
    while (!requestQueue.empty())
    {
        // lock_guard<mutex> lock(mux);
        // Processing next request
        if (!requestQueue.empty())
        {
            Request *req = requestQueue.front();
            requestQueue.pop();
            webServers.at(nextServer)->addRequest(req);
            setNextServer();
        }
    }
}

void LoadBalancer::randomlyAddRequest()
{
    while (true)
    {
        random_device rd;
        mt19937 mt(rd());
        uniform_int_distribution<int> dist(5, 10);

        auto start = chrono::steady_clock::now();
        this_thread::sleep_for(chrono::seconds(dist(mt)));
        auto end = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::seconds>(end - start);
        cout << "Elapsed time: " << duration.count() << " seconds\n";
        Request *req = new Request();
        addRequest(req);
    }
}