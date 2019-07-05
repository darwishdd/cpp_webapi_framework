// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include "../ctpl.h"
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string>
#include <iostream>
#include <string.h>
#include "../Worker/Worker.h"
#include "../RouteToWorkerMap/RouteToWorkerMap.h"
#include "../Response/Response.h"
#include "../Request/Request.h"
#include "../State/State.h"
#include "../Router/Router.h"
#include "../RoutersTree/RoutersTree.h"
#include "../Utils/Utils.h"
#define PORT 9090

class Server
{
public:
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[2 * 1024 * 1024]{};
    ctpl::thread_pool pool(10);
    std::vector<std::future<void>> threads(10);

    Server();
    void startMainLoop();
    void handleRequest(int new_socket);
};
