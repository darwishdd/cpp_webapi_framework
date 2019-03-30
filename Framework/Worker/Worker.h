#pragma once
#include <list>
#include <functional>
#include <iostream>
#include <string>
//#include req/response classes
class Request;
class Response;
//typedef int(*WorkerFunction)(int); //because ugly
typedef std::function<Response&(Request&, Response&)> WorkerFunction; //because not ugly
typedef int FunctionParameter;
typedef int FunctionReturn;

class Worker
{
	std::list<WorkerFunction> queue_{};


public:
	void push_function(WorkerFunction f);

	Response& activate(Request& request, Response& resp);
};

