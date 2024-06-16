#include <iostream>
#include <vector>
#include <random>
#include <queue>
#include <thread>
#include <unistd.h> // for getopt

#include "Request.h"
#include "Driver.h"
#include "LoadBalancer.h"
#include "WebServer.h"

using namespace std;

/**
 * @brief Fills a queue with a specified number of randomly generated requests.
 *
 * @param q Reference to the queue to be filled.
 * @param numRequests Number of requests to generate and add to the queue.
 */
void fillQueue(queue<Request *> &q, int numRequests)
{
    for (int i = 0; i < numRequests; ++i)
    {
        Request *req = new Request();
        q.push(req);
    }
}

/**
 * @brief Generates and adds requests randomly to the load balancer at intervals.
 *
 * @param lb Pointer to the LoadBalancer instance.
 */
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

/**
 * @brief Main function to simulate the load balancing process.
 *
 * This function initializes web servers, a load balancer, and threads for server processing and random request addition.
 *
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 * @return 0 if successful, 1 if there is an error in command line arguments.
 */
int main(int argc, char *argv[])
{
    int numServers = 10;
    int numClockCycles = 10000;

    // Parsing command line options
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

    // Filling the initial request queue
    queue<Request *> requestQueue;
    fillQueue(requestQueue, numServers * 100);

    // Creating each WebServer and initializing server status
    vector<WebServer *> webServers;
    vector<bool> serverStatus;
    for (int i = 0; i < numServers; ++i)
    {
        webServers.push_back(new WebServer(i + 1));
        serverStatus.push_back(false);
    }

    int start = requestQueue.size();

    // Creating a new LoadBalancer
    LoadBalancer *lb = new LoadBalancer(requestQueue, webServers, serverStatus, numClockCycles);
    
    // Threads for web servers to process requests
    vector<thread> serverThreads;
    for (int i = 0; i < numServers; ++i)
    {
        thread server(&WebServer::processRequests, webServers[i], lb);
        server.detach();
    }

    // Thread in the background for randomly adding requests to the load balancer
    thread random(randomlyAddRequest, lb);

    // Start processing requests in the load balancer
    lb->processRequests();

    // Wait for the random request addition thread to finish
    random.join();

    // Wait briefly before cleaning up
    this_thread::sleep_for(chrono::seconds(2));

    int end = lb->getRequestCount();
    cout << "Time over - done running load balancer" << endl;
    cout << "Started with " << (start - lb->getNumInvalidIP()) << " valid requests in the queue" << endl;
    cout << "Caught " << lb->getNumInvalidIP() << " invalid incoming IP addresses" << endl;
    cout << "Ended with " << end << " requests in the queue" << endl;

    // Clean up resources
    delete lb;
    for (auto server : webServers)
    {
        delete server;
    }

    return 0;
}