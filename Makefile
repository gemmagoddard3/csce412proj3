CXX=g++
CXXFLAGS=-std=c++17

all: balancer

balancer: main.o Request.o LoadBalancer.o WebServer.o
	$(CXX) $(CXXFLAGS) -o balancer main.o Request.o LoadBalancer.o WebServer.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Request.o: Request.cpp
	$(CXX) $(CXXFLAGS) -c Request.cpp

LoadBalancer.o: LoadBalancer.cpp
	$(CXX) $(CXXFLAGS) -c LoadBalancer.cpp

WebServer.o: WebServer.cpp
	$(CXX) $(CXXFLAGS) -c WebServer.cpp

clean:
	rm -f balancer *.o