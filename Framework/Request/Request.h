#pragma once
#include <string>
#include <fstream>
#include <map>
#include <sstream>

class Request_
{
public:
	std::string url;
	std::map< std::string, std::string > query;
	std::string queryString;
	std::string ip;
	std::string method;
	std::string root;
	std::string body;
	std::string headersString;
	std::map<std::string, std::string> headers;
	std::map<std::string, std::string> params;
	std::stringstream serialize();
	void deserialize(std::stringstream& sin);
};

std::ofstream& operator<< (std::ofstream& out, const Request_& request);
std::ostream& operator<< (std::ostream& out, const Request_& request);