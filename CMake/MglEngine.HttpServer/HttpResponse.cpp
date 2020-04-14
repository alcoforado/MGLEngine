#include "HttpResponse.h"

HttpResponse HttpResponse::Http500(std::string content,int version, bool keep_alive)
{
	auto res= HttpResponse(http::status::internal_server_error, version);
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.keep_alive(keep_alive);
    res.set(http::field::content_type, "text/html");
    res.body() = "An error occurred: '" + std::string(content) + "'";
    res.prepare_payload();
    return res;

}



HttpResponse HttpResponse::Http404(std::string content, int version, bool keep_alive)
{
    auto res = HttpResponse(http::status::not_found, version);
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.keep_alive(keep_alive);
    res.set(http::field::content_type, "text/html");
    res.body() = "An error occurred: '" + std::string(content) + "'";
    res.prepare_payload();
    return res;

}

HttpResponse HttpResponse::HttpOk(std::string content, int version, bool keep_alive)
{
    auto res = HttpResponse(http::status::ok, version);
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.keep_alive(keep_alive);
    res.set(http::field::content_type, "text/html");
    res.body() = content;
    res.prepare_payload();
    return res;
}


HttpResponse HttpResponse::HttpJson(std::string content, int version, bool keep_alive)
{
    auto res = HttpResponse(http::status::ok, version);
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.keep_alive(keep_alive);
    res.set(http::field::content_type, "application/json");
    res.body() = content;
    res.prepare_payload();
    return res;
}