#include "pch.h"
#include "RouteToWorkerMap.h"

Worker& RouteToWorkerMap::getWorkerByKey(const std::string& key)
{
	return routeToWorkerMap_.at(key);
}

void RouteToWorkerMap::insert(const std::string& key, Worker& worker)
{
	routeToWorkerMap_.emplace(key, worker);
}

void RouteToWorkerMap::modify(const std::string& key, Worker& worker)
{
	routeToWorkerMap_.insert_or_assign(key, worker);
}

RouteToWorkerMap::~RouteToWorkerMap()
{
	for (auto pair : routeToWorkerMap_)
	{
		delete &(pair.second);
	}
}
