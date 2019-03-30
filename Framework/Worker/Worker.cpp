#include "pch.h"
#include "Worker.h"

class Reequest;
class Response;

void Worker::push_function(WorkerFunction f)
{
	queue_.emplace_back(f);
}

Response& Worker::activate(Request& request, Response& response)
{
	for (auto f = queue_.begin(); f != queue_.end(); ++f)
	{
		(*f)(request, response);
		//if (!response) break;
	}
	return response;
}