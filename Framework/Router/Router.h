#pragma once
#include <map>
#include <functional>
#include <string>
#include "../Worker/Worker.h"
#include "../RoutersTree/RoutersTree.h"

class Router
{
	std::map<std::string, WorkerFunction> handlers_{};
	std::string path_;
	Worker middleware_{};
	std::vector<Worker*>createdWorkers{};

public:
	explicit Router(std::string path);
	void insertNewHandlerInAllRouteWorkers(const WorkerFunction& handler);
	void use(const WorkerFunction& handler);
	std::string getFullRoute(const Operation method) const;
	std::string getFullRoute(const Operation method, const std::string&customPath) const;
	void on(const Operation method, const WorkerFunction& handler);
	void on(const Operation method, const std::string& customPath, const WorkerFunction& handler);
	std::map<std::string, WorkerFunction> get_handlers() const;
};
