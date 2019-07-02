#pragma once
#include <string>
#include <vector>


void split(const std::string& str, std::vector<std::string>& cont, const char delimiter);
std::pair<std::string, std::string> splitPair(const std::string& str, const char delimiter);