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
}

int WebServer::numInQueue(){
    return serverQueue.size();
}

int WebServer::getId(){
    return serverID;
}

void WebServer::processRequests(LoadBalancer * lb){
    while(!lb->isDone()){
        // if there is a request to process
        if (!serverQueue.empty()){
            // get the next request
            Request * req = serverQueue.front();
            serverQueue.pop();
            // wait the elapsed time 
            int startTime = lb->getTime();
            // cout << "Server " << serverID << " started processing request " << req->getIpIn() << " at time " << startTime << " (" << req->getTime() << ")" << endl;
            while ((lb->getTime() - startTime) < req->getTime()){
            }
            int endTime = lb->getTime();
            // request processed, go to the next on
            cout << "Server " << serverID << " processed request " << req->getIpIn()  << " [" << startTime << "," << endTime<< "] - (" << req->getTime()  << ")";
            if(!lb->getStatus().at(serverID-1)){
                cout << "- shutting down server" << endl;
            }
            else{
                cout << endl;
            }
        }
    }
}