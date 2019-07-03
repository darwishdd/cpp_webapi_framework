#pragma once
#include <string>
#include <map>
#include <sstream>
#include <utility>
#include <vector>
#include "../Utils/Utils.h"

class Response_
{
public:
	int statusCode{};
	std::string data;
	std::map<std::string, std::string> Headers;

	void send(int StatusCode, std::string &message)
	{
		statusCode = StatusCode;
		data = std::move(message);
	}
	void send(int StatusCode, const std::string &message, const std::map<std::string, std::string> &headers)
	{
		statusCode = StatusCode;
		data = message + "<message>";
		Headers = headers;
	}
	void setHeaders(std::string &key, std::string &value)
	{
		Headers.insert({key, value});
	}
	std::stringstream serialize()
	{
		std::stringstream out;
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

		const auto current = message.find("<message>");
		data = message.substr(0, current);

		const auto HeadersString = message.substr(current + 9, message.length());
		std::vector<std::string> headerStringsVector{};
		split(HeadersString, headerStringsVector, ',');
		for (const auto &header : headerStringsVector)
		{
			Headers.insert(splitPair(std::string{header}, ':'));
		}
	}
};