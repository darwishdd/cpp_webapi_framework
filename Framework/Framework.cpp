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
	auto worker_ref = state::routeToWorkerMap.getWorkerByKey("worker");

	worker_ref.push_function([](FunctionParameter a)->FunctionReturn {
		std::cout << a; return a;
	});
	worker_ref.activate();
}
