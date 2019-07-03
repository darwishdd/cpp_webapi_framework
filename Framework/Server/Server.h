// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
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

#define PORT 9090

class Server
{
public:
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[2 * 1024 * 1024]{};
    Server()
    {
        int opt = 1;
        // Creating socket file descriptor
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }

        // Forcefully attaching socket to the port 8080
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                       &opt, sizeof(opt)))
        {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(PORT);

        // Forcefully attaching socket to the port 8080
        if (bind(server_fd, (struct sockaddr *)&address,
                 sizeof(address)) < 0)
        {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
        if (listen(server_fd, 3) < 0)
        {
            perror("listen");
            exit(EXIT_FAILURE);
        }
    }
    void startMainLoop()
    {
        while (true)
        {
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                                     (socklen_t *)&addrlen)) < 0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }
            ssize_t rsz = recv(new_socket, buffer, sizeof(buffer), 0);
            if (rsz > 0)
            {

                Request_ req{};
                Response_ res{};
                req.deserialize(buffer);
                state::routeToWorkerMap.getWorkerByKey(
                                           state::routersTree.match("/students/3/edit/5", req).operations.at(req.method).value)
                    .activate(req, res); //activates ref->ref2->ref4->ref5
                auto stream = res.serialize();
                send(new_socket, stream.str().c_str(), stream.str().length(), 0);
                shutdown(new_socket, SHUT_RDWR);
                close(new_socket);
            }
        }
    }
}
