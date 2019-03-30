class Request_
{
  private:
  public:
    Request_();
    std::wstring url;
    std::wstring host;
    std::wstring userAgent;
    std::wstring accept;
    std::vector<std::string> languages;
    std::wstring charsets;
    std::wstring authorization;
    std::wstring referer;
    std::wstring contentType;
    std::wstring root;
    std::string body;
    ~Request_();
};