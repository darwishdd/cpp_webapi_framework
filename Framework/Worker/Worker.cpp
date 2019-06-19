
#include "Worker.h"



void Worker::pushFunction(WorkerFunction f)
{
	queue_.emplace_back(f);
}

Response_& Worker::activate(Request_& request, Response_& response)
{
	for (auto f = queue_.begin(); f != queue_.end(); ++f)
	{
		const auto functionResult = (*f)(request, response);
		if (!functionResult) break;
	}

	return response;

}

void Worker::insertBeforeLast(const WorkerFunction f)
{
	auto it = queue_.end();
	--it;
	queue_.insert(it, f);
}
