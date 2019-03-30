#include "pch.h"
#include <iostream>
#include <functional>
#include <string>
#include "Worker/Worker.h"
#include "RouteToWorkerMap/RouteToWorkerMap.h"
#include "Response/Response.hpp"
#include "Request/Request.h"
#include <thread>

class state
{
public:
	static RouteToWorkerMap routeToWorkerMap;
};

RouteToWorkerMap state::routeToWorkerMap{};


int main()
{

	Worker worker;
	state::routeToWorkerMap.insert("worker", worker);
	auto worker_ref = state::routeToWorkerMap.getWorkerByKey("worker");

	worker_ref.push_function([](Request_& request, Response_& response)-> Response_&
	{

		return response;
	});
	Request_ req{};
	Response_ res{};
	worker_ref.activate(req, res);
}
