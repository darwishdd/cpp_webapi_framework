#include "pch.h"
#include "Worker.h"

void Worker::push_function(WorkerFunction f, FunctionParameter a)
{
	queue_.emplace_back(f);
	params_.emplace_back(a);
}

void Worker::activate()
{
	auto f = queue_.begin();
	auto p = params_.begin();
	for (; f != queue_.end(); ++f, ++p)
	{
		const auto status_code = (*f)(*p);
		if (status_code < 0) break;
	}
}