

#include "Worker/Worker.h"
#include "RouteToWorkerMap/RouteToWorkerMap.h"
#include "Response/Response.h"
#include "Request/Request.h"
#include "State/State.h"
#include "Router/Router.h"
#include "RoutersTree/RoutersTree.h"
//#include "RoutersTree/RoutersTree.cpp"

RouteToWorkerMap state::routeToWorkerMap{};
RoutersTree state::routersTree{};

int main()
{
	Router router{ "students" };
	const auto ref = [](Request_& request, Response_& response)-> bool {return true; };
	const auto ref2 = [](Request_& request, Response_& response)-> bool {return true; };
	const auto ref3 = [](Request_& request, Response_& response)-> bool {return true; };
	const auto ref4 = [](Request_& request, Response_& response)-> bool {return true; };
	const auto ref5 = [](Request_& request, Response_& response)-> bool {return true; };

	router.use(ref);
	router.on(GET, ref2);
	router.on(POST, "edit", ref3);
	router.use(ref4);
	router.use(ref5);

	Request_ req{};
	Response_ res{};
	state::routeToWorkerMap.getWorkerByKey("GET students").activate(req, res); //activates ref->ref2->ref4->ref5

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
