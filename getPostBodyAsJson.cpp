
#include <fastcgi++/request.hpp>
#include <fastcgi++/manager.hpp>
#include "json.hpp"

class Handler: public Fastcgipp::Request<wchar_t>
{
public:
    Handler():Fastcgipp::Request<wchar_t>(5*1024) {}

bool response() 
{
    return true;
}

protected:
    void unknownContentErrorHandler()
    {
        const std::string jsonContentType("application/json");
        auto contentType = environment().contentType;
        if (std::equal(jsonContentType.cbegin(), jsonContentType.cend(), contentType.cbegin(), contentType.cend()))
        {
            using json = nlohmann::json;
            std::string postBody(environment().postBuffer().begin(), environment().postBuffer().end());
            auto parsed = json::parse(postBody);

            out << L"Content-Type: application/json; charset=utf-8\r\n\r\n";
            out << parsed.dump().c_str();
        }
    }
};

int main() {
    Fastcgipp::Manager<Handler> manager;
    manager.setupSignals();
    manager.listen();
    manager.start();
    manager.join();

    return 0;
}