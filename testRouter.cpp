#include "Router.hpp"
#include <iostream>

bool handleGet(Request request)
{
    std::cout << "get handler\n";
    return true;
}

int main()
{
    Request request;

    Router customersRouter;
    customersRouter.path = request.path;

    customersRouter.on("get", handleGet);
    customersRouter.on("post", [](Request request) {
        std::cout << "post handler\n";
        return true;
    });

    auto customersRouteHanldlers = customersRouter.getHandleres();

    for (auto &row : customersRouteHanldlers)
    {
        std::cout << row.first << ": ";
        auto fn = row.second;
        fn(request);
        std::cout << "\n";
    }

    return 0;
}