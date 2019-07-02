#include "Utils.h"

void split(const std::string& str, std::vector<std::string>& cont, const char delimiter)
{
	std::size_t previous = 0;
	auto current = str.find(delimiter);
	while (current != std::string::npos)
	{
		cont.emplace_back(str.substr(previous, current - previous));
		previous = current + 1;
		current = str.find(delimiter, previous);
	}
	cont.emplace_back(str.substr(previous, current - previous));
}


std::pair<std::string, std::string> splitPair(const std::string& str, const char delimiter)
{
	std::pair<std::string, std::string> temp;
	auto current = str.find(delimiter);
	temp.first = str.substr(0, current);
	auto previous = current + 1;
	current = str.find(delimiter, previous);
	temp.second = str.substr(previous, current - previous);
	return temp;
}
