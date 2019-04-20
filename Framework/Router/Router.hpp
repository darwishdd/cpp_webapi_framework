#include <map>
#include <functional>
#include <string>

class Request
{
public:
    std::string path = "/api";
    std::string method = "get";
};

using Handler = std::function<bool(Request)>;

class Router
{
private:
    std::map<std::string, Handler> handlers;

public:
    std::string path;

    void on(std::string method, Handler handler)
    {
        handlers[method] = handler;
    }

    std::map<std::string, Handler> getHandleres()
    {
        return handlers;
    }
};