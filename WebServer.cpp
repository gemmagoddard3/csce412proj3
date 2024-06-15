#include "WebServer.h"
#include "Request.h"
#include "LoadBalancer.h"

#include <iostream>
#include <queue>

using namespace std;

/**
 * @brief Constructor for WebServer class.
 * 
 * Initializes a WebServer instance with a given ID.
 * 
 * @param id The ID of the server.
 */
WebServer::WebServer(int id){
    cout << "Initializing server " << id << endl;
    serverID = id;
}

/**
 * @brief Adds a request to the server's queue.
 * 
 * @param req Pointer to the Request object to be added.
 */
void WebServer::addRequest(Request * req){
    cout << "Adding " << req->getIpIn() << " to server " << serverID << endl;
    serverQueue.push(req);
}

/**
 * @brief Returns the number of requests in the server's queue.
 * 
 * @return The number of requests in the queue.
 */
int WebServer::numInQueue(){
    return serverQueue.size();
}

/**
 * @brief Returns the ID of the server.
 * 
 * @return The ID of the server.
 */
int WebServer::getId(){
    return serverID;
}

/**
 * @brief Processes requests from the server's queue.
 * 
 * This function continuously processes requests until the LoadBalancer signals it's done.
 * It waits for each request to complete processing based on its time requirement.
 * 
 * @param lb Pointer to the LoadBalancer object managing the server.
 */
void WebServer::processRequests(LoadBalancer * lb){
    while(!lb->isDone()){
        // if there is a request to process
        if (!serverQueue.empty()){
            // get the next request
            Request * req = serverQueue.front();
            serverQueue.pop();
            // wait for the elapsed time 
            int startTime = lb->getTime();
            // cout << "Server " << serverID << " started processing request " << req->getIpIn() << " at time " << startTime << " (" << req->getTime() << ")" << endl;
            while ((lb->getTime() - startTime) < req->getTime()){
            }
            int endTime = lb->getTime();
            // request processed, go to the next one
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
