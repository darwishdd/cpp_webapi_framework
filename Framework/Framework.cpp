#include "pch.h"

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
	const auto ref = [](Request_& request, Response_& response)-> bool {return true; };
	const auto ref2 = [](Request_& request, Response_& response)-> bool {return true; };
	const auto ref3 = [](Request_& request, Response_& response)-> bool {return true; };
	const auto ref4 = [](Request_& request, Response_& response)-> bool {return true; };
	const auto ref5 = [](Request_& request, Response_& response)-> bool {return true; };

	router.use(ref);
	router.on("get", ref2);
	router.on("post", ref3);
	router.use(ref4);
	router.use(ref5);

	Request_ req{};
	Response_ res{};
	state::routeToWorkerMap.getWorkerByKey("students/get").activate(req, res); //activates ref->ref2->ref4->ref5

	/*Worker worker;
	state::routeToWorkerMap.insert("worker", worker);
	auto worker_ref = state::routeToWorkerMap.getWorkerByKey("worker");

	worker_ref.pushFunction([](Request_& request, Response_& response)-> bool
	{
		return true;
	});
	Request_ req{};
	Response_ res{};
	worker_ref.activate(req, res);*/
}
