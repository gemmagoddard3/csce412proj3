#include "WebServer.h"

void WebServer::addRequest(Request * req){
    requests.push_back(req);
}