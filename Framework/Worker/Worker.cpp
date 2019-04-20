#include "pch.h"
#include "Worker.h"
#include <iterator>


void Worker::push_function(WorkerFunction f)
{
	queue_.emplace_back(f);
}

Response_& Worker::activate(Request_& request, Response_& response)
{
	for (auto f = queue_.begin(); f != queue_.end(); ++f)
	{
		const auto function_result = (*f)(request, response);
		if (!function_result) break;
	}

	return response;

}

void Worker::insert_before_last(WorkerFunction f)
{
	auto it = queue_.end();
	--it;
	queue_.insert(it, f);



}
