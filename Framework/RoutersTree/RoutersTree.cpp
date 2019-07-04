#include "RoutersTree.h"
#include "../Utils/Utils.h"
#include <iostream>
std::string RoutersTree::operationToString(const Operation operation)
{
	switch (operation)
	{
	case POST:
		return "POST";
	case PUT:
		return "PUT";
	case DELETE:
		return "DELETE";
	case GET:
	default:
		return "GET";
	}
}

void RoutersTree::add(Operation operation, const std::string &path)
{
	const auto modifiedPath = path[path.length() - 1] == '/' ? path.substr(0, path.length() - 1) : path;

	auto *currentNode = &root;
	std::vector<std::string> keys{};
	split(modifiedPath, keys, '/');
	std::string value{};
	for (auto &key : keys)
	{
		value += key + '/';
		if (currentNode->children.find(key) != currentNode->children.end())
		{
			currentNode = &currentNode->children.at(key);
		}
		else if (std::regex_match(key, std::regex(":\\w+")))
		{
			const auto param = key.substr(1, key.length());
			auto node = currentNode->children.find(":");
			if (node != currentNode->children.end())
			{
				if (node->second.parameter == param)
				{
					//found a node with the same paramter
					currentNode = &node->second;
				}
				else
				{
					//found a node with a different paramter
					node->second.parameter = param;
					node->second.value = value;
					currentNode = &node->second;
				}
			}
			else
			{
				//didn't find a parameter node
				auto newNode = new Node{true, key, param, value};
				allCreatedNodes.emplace_back(newNode);
				currentNode->children.emplace(":", *newNode);
				currentNode = newNode;
			}
		}
		else
		{
			//didn't find any node, parameter or otherwise
			auto newNode = new Node{false, key, "", value};
			allCreatedNodes.emplace_back(newNode);
			currentNode->children.emplace(key, *newNode);
			currentNode = newNode;
		}
	}
	auto operationNode = new Node{
		false, RoutersTree::operationToString(operation), "", RoutersTree::operationToString(operation) + " " + currentNode->value};
	allCreatedNodes.emplace_back(operationNode);
	operationNode->isParameter = currentNode->isParameter;
	operationNode->parameter = currentNode->parameter;
	currentNode->operations.emplace(operationToString(operation), *operationNode);
}

Node &RoutersTree::match(const std::string &path, Request_ &request)
{
	const auto modifiedPath = path[path.length() - 1] == '/' ? path.substr(0, path.length() - 1) : path;
	auto *currentNode = &root;
	std::vector<std::string> keys{};
	split(modifiedPath, keys, '/');
	for (auto &key : keys)
	{
		if (currentNode->children.find(key) != currentNode->children.end())
		{
			currentNode = &currentNode->children.at(key);
		}
		else if (currentNode->children.find(":") != currentNode->children.end())
		{
			currentNode = &currentNode->children.at(":");
			request.params.emplace(currentNode->parameter, key);
		}
		else
		{
			auto emptyNode = new Node{false, key, "", "404"};
			currentNode = emptyNode;
			//return Page404(path);
		}
	}
	return *currentNode;
}
