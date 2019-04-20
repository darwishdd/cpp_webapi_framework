#include "pch.h"
#include "Router.h"

Router::Router(const std::string path = "") : path_{ path }
{}

void Router::insertNewHandlerInAllRouteWorkers(const WorkerFunction handler)
{
	for (const auto pair : handlers_)
		state::routeToWorkerMap.getWorkerByKey(getFullRoute(pair.first)).insertBeforeLast(handler);
}

void Router::use(const WorkerFunction handler)
{
	middleware_.pushFunction(handler);
	insertNewHandlerInAllRouteWorkers(handler);
}

std::string Router::getFullRoute(const std::string& method) const
{
	return path_ + '/' + method;
}

void Router::on(const std::string method, const WorkerFunction handler)
{
	handlers_[method] = handler;
	auto worker = new Worker{ middleware_ };
	worker->pushFunction(handler);

	state::routeToWorkerMap.modify(getFullRoute(method), *worker);
}

std::map<std::string, WorkerFunction> Router::get_handleres() const
{
	return handlers_;
}
