#pragma once
#include <list>
#include <functional>
#include <iostream>
#include <string>

//typedef int(*WorkerFunction)(int); //because ugly
typedef std::function<int(int)> WorkerFunction; //because not ugly
typedef int FunctionParameter;
typedef int FunctionReturn;

class Worker
{
	std::list<WorkerFunction> queue_{};
	std::list<FunctionParameter> params_{};

public:
	void push_function(WorkerFunction f, FunctionParameter a);

	void activate();
};

