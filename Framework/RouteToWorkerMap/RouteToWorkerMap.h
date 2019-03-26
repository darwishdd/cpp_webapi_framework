#pragma once
#include <string>
#include <map>
#include "../Worker/Worker.h"

class RouteToWorkerMap
{
public:
	void insert(const std::string& key, Worker& worker);
	Worker& getWorkerByKey(std::string& key);
private:
	std::map<std::string, Worker&> routeToWorkerMap_{};
};
