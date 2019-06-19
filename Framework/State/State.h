#pragma once
#include "../RouteToWorkerMap/RouteToWorkerMap.h"
#include "../RoutersTree/RoutersTree.h"

class state
{
public:
	static RouteToWorkerMap routeToWorkerMap;
	static RoutersTree routersTree;
};
