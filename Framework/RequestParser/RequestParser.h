#include <iostream>
#include <fstream>
#include "../Request/Request.h"
#include <typeinfo>
#include "../Utils/Utils.cpp"

class RequestParser
{
public:
    Request_ request{};

    void parse(char **envp)
    {

        //body
        std::cin >> request.body;
        //main items
        request.url = getEnvironmentVariable(REQUEST_URI);
        request.ip = getEnvironmentVariable(REMOTE_ADDR);
        request.method = getEnvironmentVariable(REQUEST_METHOD);
        request.root = getEnvironmentVariable(SCRIPT_NAME);
        //queryStrings
        std::vector<std::string> queryStringsVector{};
        request.queryString = getEnvironmentVariable(QUERY_STRING);
        split(getEnvironmentVariable(QUERY_STRING), queryStringsVector, '&');
        for (auto query : queryStringsVector)
        {
            request.query.insert(splitPair(std::string{query}, '='));
        }
        //http headers
        for (char **env = envp; *env != 0; env++)
        {
            char *thisEnv = *env;
            if (std::string{thisEnv}.substr(0, 5) == "HTTP_")
            {
                request.headers.insert(splitPair(std::string{thisEnv}, '='));
            }
        }
    }
    enum EnvironmentVariable
    {
        COMSPEC,
        DOCUMENT_ROOT,
        GATEWAY_INTERFACE,
        HTTP_ACCEPT,
        HTTP_ACCEPT_ENCODING,
        HTTP_ACCEPT_LANGUAGE,
        HTTP_CONNECTION,
        HTTP_HOST,
        HTTP_USER_AGENT,
        PATH,
        QUERY_STRING,
        REMOTE_ADDR,
        REMOTE_PORT,
        REQUEST_METHOD,
        REQUEST_URI,
        SCRIPT_FILENAME,
        SCRIPT_NAME,
        SERVER_ADDR,
        SERVER_ADMIN,
        SERVER_NAME,
        SERVER_PORT,
        SERVER_PROTOCOL,
        SERVER_SIGNATURE,
        SERVER_SOFTWARE
    };

    std::string environmentVariableToString(EnvironmentVariable variable)
    {
        switch (variable)
        {
        case COMSPEC:
            return "COMSPEC";
        case DOCUMENT_ROOT:
            return "DOCUMENT_ROOT";
        case GATEWAY_INTERFACE:
            return "GATEWAY_INTERFACE";
        case HTTP_ACCEPT:
            return "HTTP_ACCEPT";
        case HTTP_ACCEPT_ENCODING:
            return "HTTP_ACCEPT_ENCODING";
        case HTTP_ACCEPT_LANGUAGE:
            return "HTTP_ACCEPT_LANGUAGE";
        case HTTP_CONNECTION:
            return "HTTP_CONNECTION";
        case HTTP_HOST:
            return "HTTP_HOST";
        case HTTP_USER_AGENT:
            return "HTTP_USER_AGENT";
        case PATH:
            return "PATH";
        case QUERY_STRING:
            return "QUERY_STRING";
        case REMOTE_ADDR:
            return "REMOTE_ADDR";
        case REMOTE_PORT:
            return "REMOTE_PORT";
        case REQUEST_METHOD:
            return "REQUEST_METHOD";
        case REQUEST_URI:
            return "REQUEST_URI";
        case SCRIPT_FILENAME:
            return "SCRIPT_FILENAME";
        case SCRIPT_NAME:
            return "SCRIPT_NAME";
        case SERVER_ADDR:
            return "SERVER_ADDR";
        case SERVER_ADMIN:
            return "SERVER_ADMIN";
        case SERVER_NAME:
            return "SERVER_NAME";
        case SERVER_PORT:
            return "SERVER_PORT";
        case SERVER_PROTOCOL:
            return "SERVER_PROTOCOL";
        case SERVER_SIGNATURE:
            return "SERVER_SIGNATURE";
        case SERVER_SOFTWARE:
            return "SERVER_SOFTWARE";
        default:
            return "";
        }
    }

    std::string getEnvironmentVariable(const std::string variable)
    {
        return getenv("variable") == 0 ? std::string{} : getenv("variable");
    }
    std::string getEnvironmentVariable(const EnvironmentVariable variable)
    {
        return getenv(environmentVariableToString(variable).c_str()) == 0 ? std::string{} : getenv(environmentVariableToString(variable).c_str());
    }
};
