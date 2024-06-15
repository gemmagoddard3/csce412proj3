#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <string>
#include <queue>
#include "Request.h"
#include "WebServer.h"

using namespace std;

/**
 * @brief The LoadBalancer class manages the distribution of requests to WebServers.
 * 
 * It maintains a queue of requests, manages the status of WebServers,
 * and tracks the time progression during request processing.
 */
class LoadBalancer
{
private:
    queue<Request *> requestQueue; /**< Queue of incoming requests */
    vector<WebServer *> webServers; /**< Vector of WebServer instances */
    vector<bool> serverStatus; /**< Vector indicating whether each server is active */
    int numServer; /**< Number of servers managed by the load balancer */
    int time; /**< Current time in the load balancer simulation */
    int endTime; /**< End time of the simulation */
    bool done; /**< Flag indicating if the load balancer has finished processing */

public:
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
    LoadBalancer(queue<Request *> rq, vector<WebServer *> ws, vector<bool> ss, int et);

    /**
     * @brief Adds a request to the load balancer's queue.
     * 
     * @param req Pointer to the Request object to be added.
     */
    void addRequest(Request *req);

    /**
     * @brief Retrieves the index of the next available server for request processing.
     * 
     * @return Index of the next available server.
     */
    int getNextServer();

    /**
     * @brief Retrieves the next request in the load balancer's queue without removing it.
     * 
     * @return Pointer to the next request in the queue.
     */
    Request *getNextInQueue();

    /**
     * @brief Processes requests in the load balancer until the simulation is complete.
     */
    void processRequests();

    /**
     * @brief Retrieves the current simulation time.
     * 
     * @return Current time in the simulation.
     */
    int getTime();

    /**
     * @brief Retrieves the end time of the simulation.
     * 
     * @return End time of the simulation.
     */
    int getEndTime();

    /**
     * @brief Increases the current time in the simulation.
     */
    void increaseTime();

    /**
     * @brief Checks if the load balancer has finished processing requests.
     * 
     * @return True if the load balancer is done, false otherwise.
     */
    bool isDone();

    /**
     * @brief Retrieves the number of requests currently in the queue.
     * 
     * @return Number of requests in the queue.
     */
    int getRequestCount();

    /**
     * @brief Retrieves the status of each server indicating if it is active or not.
     * 
     * @return Vector of boolean values indicating server status.
     */
    vector<bool> getStatus();

    /**
     * @brief Retrieves the list of active servers.
     * 
     * @note This function is not currently implemented in the provided code.
     */
    void getActiveServers();
};

#endif // LOADBALANCER_H
