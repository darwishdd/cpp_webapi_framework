#pragma once
#include <string>
#include <map>
#include "../Worker/Worker.h"

class RouteToWorkerMap
{
public:
	void insert(const std::string& key, Worker& worker);
	Worker& getWorkerByKey(const std::string& key);
	void modify(const std::string& key, Worker& worker);
	//private:
	std::map<std::string, Worker&> routeToWorkerMap_{};
	~RouteToWorkerMap();
};
