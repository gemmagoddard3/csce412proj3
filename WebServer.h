#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <string>
#include <queue>
#include <chrono>
#include "Request.h"

class LoadBalancer; // Forward declaration

using namespace std;

/**
 * @brief The WebServer class represents a web server that processes incoming requests.
 * 
 * Requests are added to a queue and processed sequentially.
 */
class WebServer
{
private:
    queue<Request *> serverQueue; /**< Queue of requests waiting to be processed */
    int serverID; /**< ID of the server */

public:
    /**
     * @brief Constructor for WebServer class.
     * 
     * Initializes a WebServer instance with a given ID.
     * 
     * @param id The ID of the server.
     */
    WebServer(int id);

    /**
     * @brief Adds a request to the server's queue.
     * 
     * @param req Pointer to the Request object to be added.
     */
    void addRequest(Request * req);

    /**
     * @brief Processes requests from the server's queue.
     * 
     * This function continuously processes requests until the LoadBalancer signals it's done.
     * 
     * @param lb Pointer to the LoadBalancer object managing the server.
     */
    void processRequests(LoadBalancer * lb);

    /**
     * @brief Returns the number of requests in the server's queue.
     * 
     * @return The number of requests in the queue.
     */
    int numInQueue();

    /**
     * @brief Returns the ID of the server.
     * 
     * @return The ID of the server.
     */
    int getId();
};

#endif // WEBSERVER_H
