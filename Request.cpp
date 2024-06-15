#include "Request.h"

Request::Request() {
    ipIn = "";
    ipOut ="";

    // Generating random ip addresses
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(100, 255);
    for(int i = 0; i < 2; i++){
        ipIn += to_string(dist(mt)) + ".";
        ipOut += to_string(dist(mt)) + ".";
    }
    ipIn += to_string(dist(mt));
    ipOut += to_string(dist(mt));

    // Generating a random time to run 
    uniform_int_distribution<int> distTime(5, 300);
    time = distTime(mt);
}

string Request::getIpIn() const
{
    return ipIn;
}

void Request::setIpIn(const string in)
{
    ipIn = in;
}

string Request::getIpOut() const
{
    return ipOut;
}

void Request::setIpOut(const string out)
{
    ipOut = out;
}

int Request::getTime() const
{
    return time;
}

void Request::setTime(int t)
{
    time = t;
}