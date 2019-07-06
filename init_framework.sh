g++ \
vote_server.cpp -L /usr/local/lib -lrestclient-cpp \
Framework/Router/Router.cpp \
Framework/Worker/Worker.cpp \
Framework/RoutersTree/RoutersTree.cpp \
Framework/Utils/Utils.cpp \
Framework/RouteToWorkerMap/RouteToWorkerMap.cpp \
Framework/Server/Server.cpp \
Framework/Request/Request.cpp \
-std=c++17 \
-pthread

