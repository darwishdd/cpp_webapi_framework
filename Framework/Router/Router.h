#include <map>
#include <functional>
#include <string>
#include "../Request/Request.h"
#include "../State/State.h"
#include "../Worker/Worker.h"

class Router
{
	std::map<std::string, WorkerFunction> handlers_{};
	std::string path_;
	Worker middleware_{};

public:
	explicit Router(std::string path);
	void insertNewHandlerInAllRouteWorkers(WorkerFunction handler);
	void use(WorkerFunction handler);
	std::string getFullRoute(const std::string& method) const;
	void on(std::string method, WorkerFunction handler);
	std::map<std::string, WorkerFunction> get_handleres() const;
};