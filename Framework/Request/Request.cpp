#include "Request.h"
#include "../Utils/Utils.h"

std::ofstream& operator<< (std::ofstream& out, const Request_& request)
{
	out << "url" << " " << request.url << std::endl;
	out << "queryString" << std::endl;
	out << "-----------" << std::endl;
	for (auto elem : request.query)
	{
		out << elem.first << " " << elem.second << std::endl;
	}
	out << "-----------" << std::endl;
	out << "ip" << " " << request.ip << std::endl;
	out << "method" << " " << request.method << std::endl;
	out << "root" << " " << request.root << std::endl;
	out << "body" << " " << request.body << std::endl;
	out << "httpHeaders" << std::endl;
	out << "-----------" << std::endl;
	for (auto elem : request.headers)
	{
		out << elem.first << " " << elem.second << std::endl;
	}
	out << "-----------" << std::endl;
	return out;
}
std::ostream& operator<< (std::ostream& out, const Request_& request)
{
	out << "url" << " " << request.url << std::endl;
	out << "queryString" << std::endl;
	out << "-----------" << std::endl;
	for (auto elem : request.query)
	{
		out << elem.first << " " << elem.second << std::endl;
	}
	out << "-----------" << std::endl;
	out << "ip" << " " << request.ip << std::endl;
	out << "method" << " " << request.method << std::endl;
	out << "root" << " " << request.root << std::endl;
	out << "body" << " " << request.body << std::endl;
	out << "httpHeaders" << std::endl;
	out << "-----------" << std::endl;
	for (auto elem : request.headers)
	{
		out << elem.first << " " << elem.second << std::endl;
	}
	out << "-----------" << std::endl;
	return out;
}

std::stringstream Request_::serialize()
{
	std::stringstream out;
	out << url << " <url>";
	out << ip << " <ip>";
	out << method << " <method>";
	out << root << " <root>";
	out << body << " <body>";
	out << queryString << " <query>";

	for (auto elem : headers)
	{
		out << elem.first << ":" << elem.second << "\n";
	}
	out << " <headers>";

	return out;

}

void Request_::deserialize(std::stringstream& sin)
{
	std::string stringkbeer{};
	std::string word{};
	while (sin >> word) {
		stringkbeer += word + " ";
	}
	std::size_t previous = 0;

	auto current = stringkbeer.find("<url>");
	url = stringkbeer.substr(previous, current);
	previous = current + 5;

	current = stringkbeer.find("<ip>");
	ip = stringkbeer.substr(previous, current - previous);
	previous = current + 4;

	current = stringkbeer.find("<method>");
	method = stringkbeer.substr(previous, current - previous);
	previous = current + 8;

	current = stringkbeer.find("<root>");
	root = stringkbeer.substr(previous, current - previous);
	previous = current + 6;

	current = stringkbeer.find("<body>");
	body = stringkbeer.substr(previous, current - previous);
	previous = current + 6;

	current = stringkbeer.find("<query>");
	queryString = stringkbeer.substr(previous, current - previous);
	previous = current + 7;

	current = stringkbeer.find("<headers>");
	headersString = stringkbeer.substr(previous, current - previous);
	previous = current + 9;


	std::vector<std::string> queryStringsVector{};
	//queryString = "a=3&b=1";
	split(queryString, queryStringsVector, '&');
	for (auto singleQuery : queryStringsVector)
	{
		query.insert(splitPair(std::string{ singleQuery }, '='));
	}

	//http headers
	std::vector<std::string> headerStringsVector{};
	//headersString = "HTTP_ACCEPT:*/*\nHTTP_ACCEPT_ENCODING:gzip, deflate\nHTTP_AUTHORIZATION:Bearer asdasjhdjkashdjagshdadh\nHTTP_CACHE_CONTROL:no - cache\nHTTP_CONNECTION : keep - alive\nHTTP_HOST : localhost\nHTTP_POSTMAN_TOKEN : 00915c67 - 95f1 - 44fc - 9eca - b1f4daac3c70\nHTTP_USER_AGENT : PostmanRuntime / 7.15.0";
	split(headersString, headerStringsVector, '\n');
	for (auto header : headerStringsVector)
	{
		headers.insert(splitPair(std::string{ header }, ':'));
	}

	return;

}
