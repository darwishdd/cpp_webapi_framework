#include "Worker/Worker.h"
#include "RouteToWorkerMap/RouteToWorkerMap.h"
#include "Response/Response.h"
#include "Request/Request.h"
#include "State/State.h"
#include "Router/Router.h"
#include "RoutersTree/RoutersTree.h"


RouteToWorkerMap state::routeToWorkerMap{};
RoutersTree state::routersTree{};

int main()
{
	//tree, add routes, and match
	// Framework.init()
	Router router{"/students/:id"};
	const auto ref = [](Request_& request, Response_& response)-> bool { return true; };
	const auto ref2 = [](Request_& request, Response_& response)-> bool { return true; };
	const auto ref3 = [](Request_& request, Response_& response)-> bool { return true; };
	const auto ref4 = [](Request_& request, Response_& response)-> bool { return true; };
	const auto ref5 = [](Request_& request, Response_& response)-> bool { return true; };

	router.use(ref);
	router.on(GET, ref2);
	router.on(POST, "edit/:id2", ref3);
	router.use(ref4);
	router.use(ref5);
	// --------------------------------------
	// Framework.run()
	Request_ req{};
	req.method = "POST";
	Response_ res{};

	state::routeToWorkerMap.getWorkerByKey(
		state::routersTree.match("/students/3/edit/5", req).operations.at(req.method).value
	).activate(req, res); //activates ref->ref2->ref4->ref5

	// -------------------------------------
}
