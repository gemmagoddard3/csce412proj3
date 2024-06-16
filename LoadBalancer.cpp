#include "LoadBalancer.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int LOAD = 50; // Global load threshold

/**
 * @brief Constructor for LoadBalancer class.
 * 
 * Initializes a LoadBalancer instance with the provided parameters.
 * 
 * @param rq Queue of requests to be managed.
 * @param ws Vector of WebServer instances to be managed.
 * @param ss Vector of server status indicating if each server is active.
 * @param et End time for the simulation.
 */
LoadBalancer::LoadBalancer(queue<Request *> rq, vector<WebServer *> ws, vector<bool> ss, int et)
{
    requestQueue = rq;
    webServers = ws;
    serverStatus = ss;
    time = 0;
    endTime = et;
    done = false;
}

/**
 * @brief Adds a request to the load balancer's queue.
 * 
 * @param req Pointer to the Request object to be added.
 */
void LoadBalancer::addRequest(Request *req)
{
    if (validateIP(req->getIpIn())){
        cout << "Adding " << req->getIpIn() << " to the request queue" << endl;
        requestQueue.push(req);
    }
    else{
        cout << "IP address " << req->getIpIn() << " blocked" << endl;
        numInvalidIP++;
    }
    
}

/**
 * @brief Retrieves the next request in the load balancer's queue without removing it.
 * 
 * @return Pointer to the next request in the queue.
 */
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

/**
 * @brief Retrieves the index of the next available server for request processing.
 * 
 * Determines which server to assign the next request based on current load and availability.
 * 
 * @return Index of the next available server.
 */
int LoadBalancer::getNextServer()
{
    int minServerIndex = 0;
    int minLoad = LOAD * 0.30;

    // Check for servers with low usage and turn them off
    for (int i = 0; i < webServers.size(); i++)
    {
        if (serverStatus.at(i) && webServers.at(i)->numInQueue() < minLoad)
        {
            cout << "Turning off server " << webServers.at(i)->getId() << endl;
            serverStatus.at(i) = false;
            getActiveServers();
        }
    }

    // Check if there is a running server already that can handle the load
    for (int i = 0; i < webServers.size(); i++)
    {
        if (serverStatus.at(i) && webServers.at(i)->numInQueue() < LOAD)
        {
            return i;
        }

        // Find the server with the smallest number of requests in queue
        if (webServers.at(i)->numInQueue() < webServers.at(minServerIndex)->numInQueue())
        {
            minServerIndex = i;
        }
    }

    // Allocate a new server if all existing servers are busy
    for (int i = 0; i < webServers.size(); i++)
    {
        if (!serverStatus.at(i))
        {
            serverStatus.at(i) = true;
            return i;
        }
    }

    return minServerIndex;
}

/**
 * @brief Processes requests in the load balancer until the simulation end time is reached.
 * 
 * Requests are assigned to servers based on load balancing algorithms.
 */
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

/**
 * @brief Retrieves the current simulation time.
 * 
 * @return Current time in the simulation.
 */
int LoadBalancer::getTime()
{
    return time;
}

/**
 * @brief Checks if the load balancer has finished processing all requests.
 * 
 * @return True if the load balancer is done, false otherwise.
 */
bool LoadBalancer::isDone()
{
    return done;
}

/**
 * @brief Increases the current time in the simulation by one unit.
 */
void LoadBalancer::increaseTime()
{
    time++;
}

/**
 * @brief Retrieves the end time of the simulation.
 * 
 * @return End time of the simulation.
 */
int LoadBalancer::getEndTime()
{
    return endTime;
}

/**
 * @brief Retrieves the total number of requests currently queued across all servers.
 * 
 * @return Total number of requests in the load balancer's queue.
 */
int LoadBalancer::getRequestCount()
{
    int count = 0;
    for (int i = 0; i < webServers.size(); i++)
    {
        count += webServers.at(i)->numInQueue();
    }
    return count;
}

/**
 * @brief Retrieves the status of each server indicating if it is active or not.
 * 
 * @return Vector of boolean values indicating server status.
 */
vector<bool> LoadBalancer::getStatus()
{
    return serverStatus;
}

/**
 * @brief Displays the IDs of active servers currently handling requests.
 * 
 * This function prints the IDs of servers that are currently active (handling requests).
 * It is primarily for debugging purposes.
 */
void LoadBalancer::getActiveServers()
{
    cout << "Active Servers ";
    for (int i = 0; i < serverStatus.size(); i++)
    {
        if (serverStatus.at(i))
        {
            cout << webServers.at(i)->getId() << " ";
        }
    }
    cout << endl;
}

/**
 * @brief Validates
 * 
 * This function validates incoming ip address by blocking ip addresses whose first three numers are greater than 
 */
bool LoadBalancer::validateIP(string ip) {
    stringstream ss(ip);
    string segment;
    int segmentCount = 0;

    while (getline(ss, segment, '.')) {
        // Convert segment to integer
        int num = stoi(segment);

        // Check the first segment only
        if (segmentCount == 0) {
            // Check if the first segment is greater than 240
            if (num > 200) {
                return false;
            }
        }
        
        segmentCount++;

        // Stop after processing the first segment
        if (segmentCount == 1) {
            break;
        }
    }

    // If the first segment is valid (<= 240)
    return true;
}

int LoadBalancer::getNumInvalidIP(){
    return numInvalidIP;
}