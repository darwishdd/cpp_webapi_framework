#pragma once
#include <list>
#include <functional>
#include <iostream>
#include <string>
#include "../Request/Request.h"
#include "../Response/Response.hpp"

//typedef int(*WorkerFunction)(int); //because ugly
typedef std::function<Response_&(Request_&, Response_&)> WorkerFunction; //because not ugly

class Worker
{
	std::list<WorkerFunction> queue_{};


public:
	void push_function(WorkerFunction f);

	Response_& activate(Request_& request, Response_& resp);
};

