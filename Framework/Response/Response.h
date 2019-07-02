#pragma once
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include "../Utils/Utils.h"

class Response_
{
public:
	int statusCode{};
	std::string data;
	std::map<std::string, std::string> Headers;

	void send(int StatusCode, std::string message)
	{
		statusCode = StatusCode;
		data = message;
	}
	void send(int StatusCode, std::string message, const std::map<std::string, std::string> headers)
	{
		statusCode = StatusCode;
		data = message + "<message>";
		Headers = headers;
	}
	void setHeaders(std::string key, std::string value)
	{
		Headers.insert({ key,value });
	}
	std::stringstream serialize() {
		std::stringstream out;
		out << data;
		int i = 0;
		for (auto elem : Headers)
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
	void deserialize(std::stringstream& sin) {
		std::string word;
		std::string Message;
		while (sin >> word)Message += word + " ";

		std::size_t previous = 0;
		auto current = Message.find("<message>");
		data = Message.substr(previous, current);

		auto HeadersString = Message.substr(current + 9, Message.length());
		std::vector<std::string> headerStringsVector{};
		split(HeadersString, headerStringsVector, ',');
		for (auto header : headerStringsVector) {
			Headers.insert(splitPair(std::string{ header }, ':'));
		}
	}
};