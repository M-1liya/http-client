#include "Request.hpp"

size_t Request::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

Request::Request()
{
}

nlohmann::json Request::GetRequest(const std::string &url)
{

    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        else
        {
            return nlohmann::json::parse(readBuffer);
        }

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();    
    return nlohmann::json();
}

nlohmann::json Request::PostRequest(const std::string& url, const std::string& postData)
{
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if(curl) 
    {
        // Устанавливаем URL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Указываем, что это POST-запрос
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        // Указываем тип контента как application/json
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Устанавливаем данные для отправки
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());

        // Выполняем запрос
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        else
        {
            return nlohmann::json();
        }
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
    curl_global_cleanup();

    return nlohmann::json();
}

nlohmann::json Request::DeleteRequest(const std::string &url)
{
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if(curl) {
        // Устанавливаем URL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        // Указываем, что это DELETE-запрос
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

        // Выполняем запрос
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        else
        {
            return nlohmann::json::parse(readBuffer);
        }

        // Освобождаем ресурсы
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    return nlohmann::json();
}

nlohmann::json Request::PatchRequest(const std::string &url, const std::string jsonData)
{
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if(curl) {
        // Устанавливаем URL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Указываем, что это PATCH-запрос
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");

        // Указываем тип контента как application/json
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Устанавливаем данные для отправки
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());

        // Выполняем запрос
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;

        // Освобождаем ресурсы
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
    curl_global_cleanup();


    
    return nlohmann::json();
}
