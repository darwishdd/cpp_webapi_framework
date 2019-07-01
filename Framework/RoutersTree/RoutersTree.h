// CPP-URL-Routing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma once

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <regex>
#include <list>

void split(const std::string& str, std::vector<std::string>& cont, const char delimiter );

enum Operation{
	GET,
	POST,
	PUT,
	DELETE
};

struct Node
{
	bool isParameter = false;
	std::string name = "";
	std::string parameter = "";
	std::string value = "";
	std::map<std::string, Node&> children{};
	std::map<Operation, Node&> operations{};
};

class RoutersTree
{
	Node root{};
	std::list<Node*> allCreatedNodes{};

public:
	//RoutersTree();
	void add(Operation operation, const std::string& path);
	Node& match(const std::string& path) ;
	static std::string operationToString(const Operation operation);
		
};

//int main()
//{
//	////tree node addition and matching test
//	const std::string test = "/users/add";
//	const std::string test1 = "/users/:id";
//	RoutersTree tree;
//	tree.add(GET, test1);
//	tree.add(POST, test);
//	auto& node = tree.match("/users/1234");
//
//	////regex test
//	std::string param = ":aasdf_sada";
//	if (std::regex_match(param, std::regex(":\\w+")))
//	{
//		param = param.substr(1, param.length());
//		std::cout << param << "\n";
//	}
//
//	////string split test
//	//	std::vector<std::string> words;
//	//	split(test, words, '/');
//	std::cout << node.operations.at(GET).value << std::endl;
//	std::cout << node.value << std::endl;
//	//    std::cout << node.operations.at(Operation::GET).parameter << std::endl;
//
//	////map stuff
//	/*std::map<std::string, int> m;
//	m.emplace("1",1);
//	auto a = m.at("1");
//	auto b = m.find("1");*/
//
//
//	return 0;
//}
