#include "Server.h"

Server::Server()
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
void Server::startMainLoop()
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
            auto &node = state::routersTree.match(req.url, req);
            std::cout << node.value << std::endl;
            std::cout << node.operations.size() << std::endl;
            trim(req.method);
            std::string notFound = "Not Found";
            if (node.operations.find(req.method) != node.operations.end())
            {
                res.send(404, &notFound);
            }
            else
            {
                state::routeToWorkerMap.getWorkerByKey(node.operations.at(req.method).value).activate(req, res); //activates ref->ref2->ref4->ref5
            }
            auto stream = res.serialize();
            send(new_socket, stream.str().c_str(), stream.str().length(), 0);
            shutdown(new_socket, SHUT_RDWR);
            close(new_socket);
        }
    }
}
