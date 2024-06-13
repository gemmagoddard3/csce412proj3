#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <iostream>
#include <random>
using namespace std;

class Request
{
private:
    string ipIn;
    string ipOut;
    int time;

public:
    Request();

    string getIpIn() const;
    void setIpIn(const string in);

    string getIpOut() const;
    void setIpOut(const string out);

    int getTime() const;
    void setTime(int t);
};

#endif