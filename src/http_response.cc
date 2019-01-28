#include "http_response.h"
#include <iostream>
#include <cstring>

std::string HttpResponse::buildStatus(std::string status)
{
    std::string httpProtocol = "HTTP/1.1 ";
    if (!status.compare(std::string("200"))) status += " OK";
    else if (!status.compare(std::string("400"))) status += " Bad Request";
    else if (!status.compare(std::string("418"))) status += " I'm a teapot"; // Not joking here
    // TODO: add other status code discribtion
    // TODO: add an enum for return status also?
    return  httpProtocol + status + "\r\n";
}

std::string HttpResponse::buildHeaders(std::string headerName, std::string headerValue)
{
    // TODO: validate headerName
    return headerName + ": " + headerValue + "\r\n";
}

std::string HttpResponse::buildBody(std::string input)
{
    return "\r\n" + input;
}

std::string HttpResponse::buildHttpResponse(std::string status, std::unordered_map<std::string, std::string> headers,
                                            std::string body)
{
    std::string res = "";
    res += HttpResponse::buildStatus(status);
    for (auto x : headers) res += HttpResponse::buildHeaders(x.first, x.second);
    res += HttpResponse::buildBody(body);

    // cout << "\n\n*******\n" << res << "********\n\n";
    return res;
}