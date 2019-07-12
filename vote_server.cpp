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
#include "json.hpp"

RouteToWorkerMap state::routeToWorkerMap{};
RoutersTree state::routersTree{};

std::string getPathEnd(std::string str, char del)
{
	return str.substr(str.find_last_of(del) + 1);
}

const auto getPolls = [](Request_ &request, Response_ &response) -> bool {
	RestClient::Response r = RestClient::get("https://vote-ff13e.firebaseio.com/polls.json");
	response.send(std::to_string(r.code), r.body);
	return true;
};
const auto getSinglePoll = [](Request_ &request, Response_ &response) -> bool {
	auto pollID = getPathEnd(request.url, '/');
	RestClient::Response r = RestClient::get("https://vote-ff13e.firebaseio.com/polls/" + pollID + ".json");
	response.send(std::to_string(r.code), r.body);
	return true;
};
const auto searchPollsByKeyword = [](Request_ &request, Response_ &response) -> bool {
	auto key = request.query.at("key");
	key = "\"" + key + "\"";
	RestClient::Response r = RestClient::get("https://vote-ff13e.firebaseio.com/polls.json?orderBy=\"keyword\"&equalTo=" + key);
	response.send(std::to_string(r.code), r.body);
	return true;
};

const auto addPoll = [](Request_ &request, Response_ &response) -> bool {
	using json = nlohmann::json;
	auto j = json::parse(request.body);
	j["count"] = 0;

	RestClient::Response r = RestClient::post("https://vote-ff13e.firebaseio.com/polls.json", "application/json", j.dump());
	response.send(std::to_string(r.code), r.body);
	return true;
};
const auto submitVote = [](Request_ &request, Response_ &response) -> bool {
	auto pollID = getPathEnd(request.url, '/');
	RestClient::Response r1 = RestClient::get("https://vote-ff13e.firebaseio.com/polls/" + pollID + ".json");
	using json = nlohmann::json;
	auto currentObject = json::parse(r1.body);
	auto userObject = json::parse(request.body);
	std::string choice = userObject["choice"];

	int total = currentObject.at("count");
	if (total == 0)
	{
		json object = json::object();
		json stats = json::object();
		stats[choice] = 1;
		object["stats"] = stats;
		object["count"] = 1;
		RestClient::Response r2 = RestClient::patch("https://vote-ff13e.firebaseio.com/polls/" + pollID + ".json", "application/json", object.dump());
		response.send(std::to_string(r2.code), r2.body);
		return true;
	}
	else
	{
		if (currentObject.at("stats").find(choice) != currentObject.at("stats").end())
		{
			int current = currentObject.at("stats").at(choice);
			currentObject.at("stats").at(choice) = current + 1;
			currentObject["count"] = total + 1;
			RestClient::Response r2 = RestClient::patch("https://vote-ff13e.firebaseio.com/polls/" + pollID + ".json", "application/json", currentObject.dump());
			response.send(std::to_string(r2.code), r2.body);
			return true;
		}
		else
		{
			json object = currentObject;
			json stats = currentObject.at("stats");
			stats[choice] = 1;
			object["stats"] = stats;
			object["count"] = total + 1;
			RestClient::Response r2 = RestClient::patch("https://vote-ff13e.firebaseio.com/polls/" + pollID + ".json", "application/json", object.dump());
			response.send(std::to_string(r2.code), r2.body);
			return true;
		}
	}
};

const auto deleteVote = [](Request_ &request, Response_ &response) -> bool {
	auto pollID = getPathEnd(request.url, '/');
	RestClient::Response r = RestClient::del("https://vote-ff13e.firebaseio.com/polls/" + pollID + ".json");
	response.send(std::to_string(r.code), r.body);
	return true;
};

int main()
{
	Router pollsRouter{"/cgi-bin/api/polls"};

	pollsRouter.on(GET, getPolls);
	pollsRouter.on(GET, ":id", getSinglePoll);
	pollsRouter.on(GET, "search", searchPollsByKeyword);

	pollsRouter.on(POST, addPoll);
	pollsRouter.on(PUT, ":id", submitVote);
	// pollsRouter.on(POST, ":id", submitVote);


	pollsRouter.on(DELETE, ":id", deleteVote);
	// pollsRouter.on(POST, "delete/:id", deleteVote);

	Server server{};
	server.startMainLoop();
}
