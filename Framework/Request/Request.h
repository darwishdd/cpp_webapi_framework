#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include "../RoutersTree/RoutersTree.h"

class Request_
{
public:
	std::string url;
	std::map< std::string , std::string > query;
	std::string queryString;
	std::string ip;
	std::string method;
	std::string root;
	std::string body;
	std::string headersString;
	std::map<std::string, std::string> headers;
	std::stringstream serialize();
	void deserialize(std::stringstream& sin);
	std::pair<std::string, std::string> splitPair(const std::string& str, const char delimiter = ' ');
	
};

std::ofstream& operator<< (std::ofstream& out, const Request_& request);
std::ostream& operator<< (std::ostream& out, const Request_& request);