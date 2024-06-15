#include <iostream>
#include <vector>
#include <random>
#include <queue>
#include <thread>
#include <unistd.h>  // for getopt

#include "Request.h"
#include "LoadBalancer.h"
#include "WebServer.h"

using namespace std;

void fillQueue(queue<Request *> &q, int numRequests) {
    for (int i = 0; i < numRequests; ++i) {
        Request *req = new Request();
        q.push(req);
    }
}

void randomlyAddRequest(LoadBalancer *lb) {
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(1, 100);

    while (true) {
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

int main(int argc, char *argv[]) {
    int numServers = 10;
    int numClockCycles = 10000;

    int opt;
    while ((opt = getopt(argc, argv, "s:c:")) != -1) {
        switch (opt) {
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
    fillQueue(requestQueue, 10);

    vector<WebServer *> webServers;
    vector<bool> serverStatus;

    cout << "Starting with " << requestQueue.size() << " elements in the queue" << endl;

    // creating each WebServer
    for (int i = 0; i < numServers; ++i) {
        webServers.push_back(new WebServer(i + 1));
        serverStatus.push_back(false);
    }

    // creating a new load balancer
    LoadBalancer *lb = new LoadBalancer(requestQueue, webServers, serverStatus, numClockCycles);

    //  // creating threads for each WebServer
    for (int i = 0; i < numServers; ++i) {
        thread serverThread(&WebServer::processRequests, webServers.at(i), lb);
        serverThread.detach();  // Detach thread to let it run independently
    }

    // thread in the background for randomly adding requests to the load balancer
    thread addRequestThread(randomlyAddRequest, lb);
    addRequestThread.detach();

    lb->processRequests();

    // Clean up
    delete lb;
    for (auto server : webServers) {
        delete server;
    }

    return 0;
}