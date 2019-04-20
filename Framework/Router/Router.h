#include <map>
#include <functional>
#include <string>
#include "../Request/Request.h"
#include "../State/State.h"
#include "../Worker/Worker.h"



class Router
{
	std::map<std::string, WorkerFunction> handlers;
	std::string path;
	Worker middleware;

public:
	Router(std::string path = "") : path{ path }
	{}

	void refresh_all_routes(WorkerFunction handler)
	{
		for (auto f : handlers)
			state::routeToWorkerMap.getWorkerByKey(get_full_route(f.first)).insert_before_last(handler);
	}

	void use(WorkerFunction handler)
	{
		middleware.push_function(handler);
		refresh_all_routes(handler);
	}

	std::string get_full_route(const std::string& method)
	{
		return path + '/' + method;
	}

	void on(std::string method, WorkerFunction handler)
	{
		handlers[method] = handler;
		Worker* worker = new Worker{ middleware };
		worker->push_function(handler);

		state::routeToWorkerMap.modify(get_full_route(method), *worker);
	}

	std::map<std::string, WorkerFunction> getHandleres()
	{
		return handlers;
	}
};