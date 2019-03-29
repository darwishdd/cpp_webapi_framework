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
