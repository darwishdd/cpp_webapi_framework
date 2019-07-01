#include "RoutersTree.h"


void split(const std::string& str, std::vector<std::string>& cont, const char delimiter = ' ')
{
	std::size_t previous = 0;
	auto current = str.find(delimiter);
	while (current != std::string::npos)
	{
		cont.emplace_back(str.substr(previous, current - previous));
		previous = current + 1;
		current = str.find(delimiter, previous);
	}
	cont.emplace_back(str.substr(previous, current - previous));
}


std::string RoutersTree::operationToString(const Operation operation) {
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

void RoutersTree::add(Operation operation, const std::string & path) {
	auto* currentNode = &root;
	std::vector<std::string> keys{};
	split(path, keys, '/');
	std::string value{};
	for (const auto& key : keys)
	{
		value += key + '/';
		if (currentNode->children.find(key) != currentNode->children.end())
		{
			currentNode = &currentNode->children.at(key);
		}
		else
		{
			auto newNode = new Node{ false, key, "", value };
			auto mapKey = key;
			allCreatedNodes.emplace_back(newNode);
			if (std::regex_match(key, std::regex(":\\w+")))
			{
				const auto param = key.substr(1, key.length());
				newNode->isParameter = true;
				newNode->parameter = param;
				mapKey = ":";
			}
			currentNode->children.emplace(mapKey, *newNode);
			currentNode = newNode;
		}
	}
	auto operationNode = new Node{
		false, RoutersTree::operationToString(operation), "", RoutersTree::operationToString(operation) + " " + currentNode->value
	};
	allCreatedNodes.emplace_back(operationNode);
	operationNode->isParameter = currentNode->isParameter;
	operationNode->parameter = currentNode->parameter;
	currentNode->operations.emplace(operation, *operationNode);
}

Node& RoutersTree::match(const std::string & path) 
{
	auto* currentNode = &root;
	std::vector<std::string> keys{};
	split(path, keys, '/');
	for (const auto& key : keys)
	{
		if (currentNode->children.find(key) != currentNode->children.end())
		{
			currentNode = &currentNode->children.at(key);
		}
		else if (currentNode->children.find(":") != currentNode->children.end())
		{
			currentNode = &currentNode->children.at(":");
		}
		else
		{
			//return Page404(path);
		}
	}
	return *currentNode;
}
