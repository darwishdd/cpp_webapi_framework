#include "pch.h"
#include <iostream>
#include <functional>
#include <string>
#include <thread>

#include "Worker/Worker.h"
#include "RouteToWorkerMap/RouteToWorkerMap.h"
#include "Response/Response.h"
#include "Request/Request.h"
#include "State/State.h"
#include "Router/Router.h"


RouteToWorkerMap state::routeToWorkerMap{};


int main()
{
	Router router{ "students" };
	auto ref = [](Request_& request, Response_& response)-> bool {return true; };

	router.use(ref);
	router.on("get", ref);
	router.on("post", ref);

	Request_ req{};
	Response_ res{};
	state::routeToWorkerMap.getWorkerByKey("students/get").activate(req, res);

	router.use(ref);
	router.use(ref);


	/*Worker worker;
	state::routeToWorkerMap.insert("worker", worker);
	auto worker_ref = state::routeToWorkerMap.getWorkerByKey("worker");

	worker_ref.push_function([](Request_& request, Response_& response)-> bool
	{
		return true;
	});
	Request_ req{};
	Response_ res{};
	worker_ref.activate(req, res);*/
}
