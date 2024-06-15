#include "Request.h"

/**
 * @brief Default constructor for Request class.
 * 
 * Initializes ipIn and ipOut with random IP addresses and generates a random time.
 */
Request::Request()
{
    ipIn = "";
    ipOut = "";

    // Generating random ip addresses
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(100, 255);
    for (int i = 0; i < 2; i++)
    {
        ipIn += to_string(dist(mt)) + ".";
        ipOut += to_string(dist(mt)) + ".";
    }
    ipIn += to_string(dist(mt));
    ipOut += to_string(dist(mt));

    // Generating a random time to run
    uniform_int_distribution<int> distTime(5, 200);
    time = distTime(mt);
}

/**
 * @brief Getter function for ipIn.
 * 
 * @return The current value of ipIn.
 */
string Request::getIpIn() const
{
    return ipIn;
}

/**
 * @brief Setter function for ipIn.
 * 
 * @param in The new value to set for ipIn.
 */
void Request::setIpIn(const string in)
{
    ipIn = in;
}

/**
 * @brief Getter function for ipOut.
 * 
 * @return The current value of ipOut.
 */
string Request::getIpOut() const
{
    return ipOut;
}

/**
 * @brief Setter function for ipOut.
 * 
 * @param out The new value to set for ipOut.
 */
void Request::setIpOut(const string out)
{
    ipOut = out;
}

/**
 * @brief Getter function for time.
 * 
 * @return The current value of time.
 */
int Request::getTime() const
{
    return time;
}

/**
 * @brief Setter function for time.
 * 
 * @param t The new value to set for time.
 */
void Request::setTime(int t)
{
    time = t;
}