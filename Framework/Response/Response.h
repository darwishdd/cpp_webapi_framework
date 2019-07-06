#pragma once
#include <string>
#include <map>
#include <sstream>
#include <utility>
#include <vector>
#include "../Utils/Utils.h"
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

class Response_
{
public:
	std::string statusCode{};
	std::string data;
	std::map<std::string, std::string> Headers;

	void send(std::string StatusCode, std::string &message)
	{
		statusCode = StatusCode;
		data = "<status>" +message + "<message>";
	}
	void send(std::string StatusCode, const std::string &message, const std::map<std::string, std::string> &headers)
	{
		statusCode = StatusCode;
		data = "<status>" +message + "<message>";
		Headers = headers;
	}
	 void sendToUser()
    {
        std::cout << "Status: " + statusCode + "/n";
        std::cout << "Content-Type: application/json\r\n\r\n";
        std::cout << data;
    }
	void setHeaders(std::string &key, std::string &value)
	{
		Headers.insert({key, value});
	}
	std::stringstream serialize()
	{
		std::stringstream out;
		out << statusCode;
		out << data;
		
		unsigned int i = 0;
		for (const auto &elem : Headers)
		{
			if (Headers.size() - 1 == i)
			{
				out << elem.first << ":" << elem.second;
				break;
			}
			out << elem.first << ":" << elem.second << ",";
			i++;
		}

		return out;
	}
	void deserialize(char *bin)
	{
		std::stringstream sin{bin};
		std::string message{sin.str()};

		std::size_t previous = 0;
		auto current = message.find("<status>");
		statusCode = message.substr(previous, current);
		previous = current + 8;

		current = message.find("<message>");
		data = message.substr(previous,current-previous);
		previous = current + 9;

		auto HeadersString = message.substr(previous, message.length());
		std::vector<std::string> headerStringsVector{};
		split(HeadersString, headerStringsVector, ',');
		for (auto header : headerStringsVector) {
			Headers.insert(splitPair(std::string{ header }, ':'));
		}
	}
};