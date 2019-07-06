#include "Framework/Worker/Worker.h"
#include "Framework/RouteToWorkerMap/RouteToWorkerMap.h"
#include "Framework/Response/Response.h"
#include "Framework/Request/Request.h"
#include "Framework/State/State.h"
#include "Framework/Router/Router.h"
#include "Framework/RoutersTree/RoutersTree.h"
#include "Framework/Server/Server.h"
#include <iostream>
#include <restclient-cpp/restclient.h>

RouteToWorkerMap state::routeToWorkerMap{};
RoutersTree state::routersTree{};

std::string getPathEnd(std::string str, char del)
{
	return str.substr(str.find_last_of(del) + 1);
}

int main()
{
	Router pollsRouter{"/cgi-bin/api/polls"};

	const auto getPolls = [](Request_ &request, Response_ &response) -> bool {
		RestClient::Response r = RestClient::get("https://vote-ff13e.firebaseio.com/polls.json");
		response.send("200", r.body);
		return true;
	};

	const auto getSinglePoll = [](Request_ &request, Response_ &response) -> bool {
		auto pollID = getPathEnd(request.url, '/');
		RestClient::Response r = RestClient::get("https://vote-ff13e.firebaseio.com/polls/" + pollID + ".json");
		response.send("200", r.body);
		return true;
	};

	pollsRouter.on(GET, getPolls);
	pollsRouter.on(GET, ":id", getSinglePoll);
	Server server{};
	server.startMainLoop();
}

