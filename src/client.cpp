#include "Requests/Request.hpp"
#include <curl/curl.h>
#include <nlohmann/json.hpp>


std::string base64_encode(const std::string &in) 
{
    std::string out;
    int val = 0;
    int valb = -6;
    std::string base64_chars = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    for (unsigned char c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back(base64_chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) {
        out.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
    }
    while (out.size() % 4) {
        out.push_back('=');
    }
    return out;
}

std::string getDataForSignUp()
{
    nlohmann::json request;

    std::string username, email, password; 
    std::cout << "Entert uname, email and password\n";

    std::cin >> username >> email >> password;
    request["username"] = username;
    request["email"] = email;
    request["password"] = password;

    return request.dump();
}

std::string getDataForUpdate()
{
    nlohmann::json request;

    std::string ur_username, ur_password, new_username, new_email, new_password; 

    std::cout << "Enter yours username and password\n";
    std::cin >> ur_username >> ur_password;

    std::cout << "\nEnter new username, email and/or password\n" << "(enter '\\' to skip field)\n";
    std::cin >> new_username >> new_email >> new_password;

    request["authoriztaion"] = "Basic " + base64_encode(ur_username + ":" + ur_password);

    if(new_username != "\\")
        request["username"] = new_username;
    if(new_email != "\\")
        request["email"] = new_email;
    if(new_password != "\\")
        request["password"] = new_password;

    return request.dump();
}

int main() 
{
    std::string url = "http://localhost:8080";
    Request Requester;
    nlohmann::json response;

    int choice;

    do
    {
        std::cout << "\n------------MENU------------" << std::endl;
        std::cout << "1. Get users" << std::endl;
        std::cout << "2. Sign up user" << std::endl;
        std::cout << "3. Delete user" << std::endl;
        std::cout << "4. Update user" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "----------------------------" << std::endl;

        
        std::cin >> choice;
        std::string userId;

        switch (choice)
        {
        case 1:
            response = Requester.GetRequest(url + "/users");
            std::cout << "response:\n" << response.dump(2) << std::endl;
            break;

        case 2:
            response = Requester.PostRequest(url + "/signup", getDataForSignUp());
            break;
        case 3:

            std::cout << "Enter user's id: ";
            std::cin >> userId;

            Requester.DeleteRequest(url + "/users/" + userId);
            break;

        case 4:
            std::cout << "Enter user's id for update: ";
            std::cin >> userId;

            Requester.PatchRequest(url + "/users/" + userId, getDataForUpdate());
            break;

        default:
            break;
        }
    } while (choice != 0);

    return 0;
}
