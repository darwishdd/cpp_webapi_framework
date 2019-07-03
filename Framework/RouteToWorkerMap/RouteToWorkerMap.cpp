
#include "RouteToWorkerMap.h"

Worker& RouteToWorkerMap::getWorkerByKey(const std::string& key)
{
	const auto modifiedKey = key[key.length() - 1] == '/' ? key.substr(0, key.length() - 1) : key;
	return routeToWorkerMap_.at(modifiedKey);
}

void RouteToWorkerMap::insert(const std::string& key, Worker& worker)
{
	routeToWorkerMap_.emplace(key, worker);
}

void RouteToWorkerMap::modify(const std::string& key, Worker& worker)
{
	routeToWorkerMap_.insert_or_assign(key, worker);
}
