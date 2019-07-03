#pragma once
#include <list>
#include <functional>

#include "../Request/Request.h"
#include "../Response/Response.h"

//typedef int(*WorkerFunction)(int); //because ugly
typedef std::function<bool(Request_&, Response_&)> WorkerFunction; //because not ugly

class Worker
{
	std::list<WorkerFunction> queue_{};

public:


	void pushFunction(WorkerFunction f);

	Response_& activate(Request_& request, Response_& response);

	void insertBeforeLast(WorkerFunction f);

};

