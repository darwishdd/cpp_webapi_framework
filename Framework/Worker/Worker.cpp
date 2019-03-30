#include "pch.h"
#include "Worker.h"


void Worker::push_function(WorkerFunction f)
{
	queue_.emplace_back(f);
}

Response_& Worker::activate(Request_& request, Response_& response)
{
	for (auto f = queue_.begin(); f != queue_.end(); ++f)
	{
		(*f)(request, response);
		//if (!response) break;
	}
	return response;
}