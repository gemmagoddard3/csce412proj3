#include "WebServer.h"
#include "Request.h"
#include "LoadBalancer.h"

#include <string>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <queue>
#include <thread>

using namespace std;

WebServer::WebServer(int id){
    cout << "Initializing server " << id << endl;
    serverID = id;
}

void WebServer::addRequest(Request * req){
    cout << "Adding " << req->getIpIn() << " to server " << serverID << endl;
    serverQueue.push(req);
    // cout << serverQueue.size() << endl;
}

int WebServer::numInQueue(){
    return serverQueue.size();
}

void WebServer::processRequests(LoadBalancer * lb){
    while(lb->getTime() < lb->getEndTime()){
        // if there is a request to process
        if (!serverQueue.empty()){
            // get the next request
            Request * req = serverQueue.front();
            serverQueue.pop();
            cout << "Server " << serverID << " processing request " << req->getIpIn() << endl;

            // wait the elapsed time 
            int startTime = lb->getTime();
            while ((lb->getTime() - startTime) > req->getTime()){
                cout << "time ticking";
            }
            // request processed, go to the next on
            cout << "At " << lb->getTime() << " " << serverID << " processed " << req->getIpIn() << endl;
        }
    }
}