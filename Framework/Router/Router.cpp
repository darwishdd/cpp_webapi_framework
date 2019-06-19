#include "Router.h"
#include <utility>
#include "../State/State.h"
#include "../RoutersTree/RoutersTree.h"


Router::Router(std::string path = "") : path_{std::move(path)}
{}

void Router::insertNewHandlerInAllRouteWorkers(const WorkerFunction& handler)
{
	for (const auto& pair : handlers_)
		state::routeToWorkerMap.getWorkerByKey(pair.first).insertBeforeLast(handler);
}

void Router::use(const WorkerFunction& handler)
{
	middleware_.pushFunction(handler);
	insertNewHandlerInAllRouteWorkers(handler);
}

std::string Router::getFullRoute(const Operation method) const
{
	return RoutersTree::operationToString(method)+' '+path_;
	
}
std::string Router::getFullRoute(const Operation method ,const std::string& customPath) const
{
	return RoutersTree::operationToString(method)+' '+path_+'/'+customPath;
}

void Router::on(const Operation method, const WorkerFunction& handler)
{
	state::routersTree.add(method, path_);
	handlers_[getFullRoute(method)] = handler;
	auto worker = new Worker{ middleware_ };
	worker->pushFunction(handler);
	createdWorkers.emplace_back(worker);
	state::routeToWorkerMap.modify(getFullRoute(method), *worker);
}


void Router::on(const Operation method, const std::string& customPath, const WorkerFunction& handler)
{
	state::routersTree.add(method,path_+'/'+customPath);
	handlers_[getFullRoute(method, customPath)] = handler;
	auto worker = new Worker{ middleware_ };
	worker->pushFunction(handler);
	createdWorkers.emplace_back(worker);
	state::routeToWorkerMap.modify(getFullRoute(method, customPath), *worker);
}

std::map<std::string, WorkerFunction> Router::get_handlers() const
{
	return handlers_;
}
