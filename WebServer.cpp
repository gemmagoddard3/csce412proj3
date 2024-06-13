#include "WebServer.h"
#include "Request.h"

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

using namespace std;

WebServer::WebServer(int id){
    cout << "Initializing server " << id << endl;
    serverID = id;
}

void WebServer::addRequest(Request * req){
    // lock_guard<mutex> lock(mux);
    cout << "Adding " << req->getIpIn() << " to server " << serverID << endl;
    serverQueue.push(req);
}

void WebServer::processRequests(){
    while(true){
        // lock_guard<mutex> lock(mux);
        // Processing next request
        if (!serverQueue.empty()){
             Request * elem = serverQueue.front();
            serverQueue.pop();
            cout << "Server " << serverID << "processing request " << elem->getIpIn() << " for " << elem->getTime() << " seconds." << endl;
            this_thread::sleep_for(chrono::seconds(elem->getTime()));
            cout << "Server " << serverID << ": " << elem->getIpIn() << " finished." << endl;
        }
        // No requests, wait 1 second to check again 
        else{
            cout << "No requests in server queue" << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
}