#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <locale>

void split(const std::string &str, std::vector<std::string> &cont, const char delimiter);
std::pair<std::string, std::string> splitPair(const std::string &str, const char delimiter);
// trim from start (in place)
static inline void ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
                return !std::isspace(ch);
            }));
}

// trim from end (in place)
static inline void rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
                return !std::isspace(ch);
            })
                .base(),
            s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s)
{
    ltrim(s);
    rtrim(s);
}