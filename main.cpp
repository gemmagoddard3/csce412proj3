#include <iostream>
#include <vector>
#include <random>
#include <queue>
#include <thread>
#include <unistd.h> // for getopt

#include "Request.h"
#include "LoadBalancer.h"
#include "WebServer.h"

using namespace std;

void fillQueue(queue<Request *> &q, int numRequests)
{
    for (int i = 0; i < numRequests; ++i)
    {
        Request *req = new Request();
        q.push(req);
    }
}

void randomlyAddRequest(LoadBalancer *lb)
{
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(500, 1000);

    while (!lb->isDone())
    {
        auto start = chrono::steady_clock::now();
        this_thread::sleep_for(chrono::milliseconds(dist(mt)));
        auto end = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

        Request *req = new Request();
        cout << "Randomly adding request with IP address " << req->getIpIn()
             << " after " << duration.count() << " milliseconds." << endl;

        lb->addRequest(req);
    }
}

int main(int argc, char *argv[])
{
    int numServers = 10;
    int numClockCycles = 10000;

    int opt;
    while ((opt = getopt(argc, argv, "s:c:")) != -1)
    {
        switch (opt)
        {
        case 's':
            numServers = stoi(optarg);
            break;
        case 'c':
            numClockCycles = stoi(optarg);
            break;
        default:
            cerr << "Usage: " << argv[0] << " -s <numServers> -c <time>" << endl;
            return 1;
        }
    }

    queue<Request *> requestQueue;
    fillQueue(requestQueue, numServers*100);

    // creating each WebServer
    vector<WebServer *> webServers;
    vector<bool> serverStatus;
    for (int i = 0; i < numServers; ++i)
    {
        webServers.push_back(new WebServer(i + 1));
        serverStatus.push_back(false);
    }

    int start = requestQueue.size();
    // creating a new load balancer
    LoadBalancer *lb = new LoadBalancer(requestQueue, webServers, serverStatus, numClockCycles);
    

    // threads for web servers to process requests
    vector<thread> serverThreads;
    for (int i = 0; i < numServers; ++i)
    {
        thread server(&WebServer::processRequests, webServers[i], lb);
        server.detach();
    }

    // thread in the background for randomly adding requests to the load balancer
    thread random(randomlyAddRequest, lb);

    lb->processRequests();
    random.join();

    this_thread::sleep_for(chrono::seconds(2));

    int end = lb->getRequestCount();
    cout << "Time over - done running load balancer" << endl;
    cout << "Started with " << start << " elements in the queue" << endl;
    cout << "Ended with " << end << " elements in the queue" << endl;

    delete lb;
    for (auto server : webServers)
    {
        delete server;
    }

    return 0;
}