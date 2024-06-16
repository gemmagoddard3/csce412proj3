#ifndef DRIVER_H
#define DRIVER_H

#include <iostream>
#include <vector>
#include <random>
#include <queue>
#include <thread>
#include <unistd.h> // for getopt

#include "Request.h"
#include "LoadBalancer.h"
#include "WebServer.h"

using namespace std;

/**
 * @file Driver.h
 * @brief Header file for Load Balancer simulation driver functions.
 */

/**
 * @brief Fills a queue with a specified number of randomly generated requests.
 *
 * @param q Reference to the queue to be filled.
 * @param numRequests Number of requests to generate and add to the queue.
 */
void fillQueue(queue<Request *> &q, int numRequests);

/**
 * @brief Generates and adds requests randomly to the load balancer at intervals.
 *
 * @param lb Pointer to the LoadBalancer instance.
 */
void randomlyAddRequest(LoadBalancer *lb);

/**
 * @brief Main function to simulate the load balancing process.
 *
 * This function initializes web servers, a load balancer, and threads for server processing and random request addition.
 *
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 * @return 0 if successful, 1 if there is an error in command line arguments.
 */
int main(int argc, char *argv[]);

#endif // DRIVER_H
