// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include "Response/Response.h"
#include "Request/Request.h"
#include "RequestParser/RequestParser.h"

#define PORT 9090

int main(int argc, char **argv, char **envp)
{
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}

	
	Request_ request = parseRequest(envp);

	auto requestString = request.serialize();

	std::string responseString{};
	send(sock, requestString.str().c_str(), requestString.str().length(), 0);

	char buffer[1024]{};
	valread = read(sock, buffer, 1024);

	Response_ res{};
	res.deserialize(buffer);
	res.sendToUser();
	return 0;
}
