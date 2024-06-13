#include <string>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "Request.h"
#include <queue>
#include <thread>

using namespace std;
using namespace std::chrono;

void createNewRequest(queue<Request *> &q)
{
    Request *req = new Request();
    q.push(req);
}

void fillQueue(queue<Request *> &q, int numServers)
{
    for (int i = 0; i < numServers * 100; i++)
    {
        createNewRequest(q);
    }
}

void randomlyAddRequest(queue<Request *> &q)
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

        // Output the elapsed time (optional)
        cout << "Elapsed time: " << duration.count() << " seconds\n";
        createNewRequest(q);
    }
}

void printQueue(queue<Request *> q)
{
    while (!q.empty())
    {
        Request *elem = q.front();
        cout << "IP IN: " << elem->getIpIn() << "   IP OUT: " << elem->getIpOut() << "   TIME: " << elem->getTime() << endl;
        delete elem;
        q.pop();
    }
    cout << endl;
}

int main(int argc, char *argv[])
{

    int opt;
    int numServers = 10;
    int numClockCycles = 10000;

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

    fillQueue(requestQueue, 10);
    randomlyAddRequest(requestQueue);

    this_thread::sleep_for(seconds(15));
    // printQueue(requestQueue);

    // vector<Request*> tasks;

    // Request * req = new Request("192.168.1.1", "10.0.0.1", 60);

    // tasks.push_back(req);

    // cout << "Initial IP In: " << tasks.at(0)->getIpIn() << endl;
    // cout << "Initial IP Out: " << tasks.at(0)->getIpOut() << endl;
    // cout << "Initial Time: " << tasks.at(0)->getTime() << endl;

    // tasks.at(0)->setIpIn("172.16.0.1");
    // tasks.at(0)->setIpOut("192.168.0.1");
    // tasks.at(0)->setTime(120);

    // cout << "Updated IP In: " << tasks.at(0)->getIpIn() << endl;
    // cout << "Updated IP Out: " << tasks.at(0)->getIpOut() << endl;
    // cout << "Updated Time: " << tasks.at(0)->getTime() << endl;
}