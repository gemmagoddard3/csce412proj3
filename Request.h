#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <iostream>
#include <random>
using namespace std;

/**
 * @brief The Request class represents a network request with source and destination IP addresses and a duration.
 */
class Request
{
private:
    string ipIn; /**< The source IP address */
    string ipOut; /**< The destination IP address */
    int time; /**< The time duration of the request */

public:
    /**
     * @brief Default constructor for Request class.
     * 
     * Initializes ipIn and ipOut with random IP addresses and generates a random time.
     */
    Request();

    /**
     * @brief Getter function for ipIn.
     * 
     * @return The current value of ipIn.
     */
    string getIpIn() const;

    /**
     * @brief Setter function for ipIn.
     * 
     * @param in The new value to set for ipIn.
     */
    void setIpIn(const string in);

    /**
     * @brief Getter function for ipOut.
     * 
     * @return The current value of ipOut.
     */
    string getIpOut() const;

    /**
     * @brief Setter function for ipOut.
     * 
     * @param out The new value to set for ipOut.
     */
    void setIpOut(const string out);

    /**
     * @brief Getter function for time.
     * 
     * @return The current value of time.
     */
    int getTime() const;

    /**
     * @brief Setter function for time.
     * 
     * @param t The new value to set for time.
     */
    void setTime(int t);
};

#endif // REQUEST_H
