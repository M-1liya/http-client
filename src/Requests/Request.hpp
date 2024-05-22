#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <string>

class Request
{
private:
    /* data */
    std::string url;
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

public:
    Request();
    ~Request() = default;


    nlohmann::json GetRequest(const std::string& url) ;
    nlohmann::json PostRequest(const std::string& url, const std::string& postData) ;
    nlohmann::json DeleteRequest(const std::string& url) ;
    nlohmann::json PatchRequest(const std::string &url, const std::string jsonData) ;
};


#endif //REQUEST_H
