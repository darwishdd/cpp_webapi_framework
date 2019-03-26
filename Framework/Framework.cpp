#include "pch.h"
#include <iostream>
#include <functional>
#include <string>
#include "Worker/Worker.h"
#include "RouteToWorkerMap/RouteToWorkerMap.h"

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
	auto worker_name = static_cast<std::string>("worker");
	auto worker_ref = state::routeToWorkerMap.getWorkerByKey(worker_name);

	worker_ref.push_function([](FunctionParameter a)->FunctionReturn {
		std::cout << a; return a;
	}, 6);
	worker_ref.activate();
}
