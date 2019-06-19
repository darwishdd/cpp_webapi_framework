#pragma once
#include <vector>
#include <string>

class Request_
{
public:
	Request_() = default;
	std::wstring url;
	std::wstring host;
	std::wstring userAgent;
	std::wstring accept;
	std::vector<std::string> languages{};
	std::wstring charsets;
	std::wstring authorization;
	std::wstring referer;
	std::wstring contentType;
	std::wstring root;
	std::string body;
	~Request_() = default;
};

