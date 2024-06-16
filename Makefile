CXX=g++
CXXFLAGS=-std=c++17

all: balancer

balancer: Driver.o Request.o LoadBalancer.o WebServer.o
	$(CXX) $(CXXFLAGS) -o balancer Driver.o Request.o LoadBalancer.o WebServer.o

Driver.o: Driver.cpp
	$(CXX) $(CXXFLAGS) -c Driver.cpp

Request.o: Request.cpp
	$(CXX) $(CXXFLAGS) -c Request.cpp

LoadBalancer.o: LoadBalancer.cpp
	$(CXX) $(CXXFLAGS) -c LoadBalancer.cpp

WebServer.o: WebServer.cpp
	$(CXX) $(CXXFLAGS) -c WebServer.cpp

clean:
	rm -f balancer *.o