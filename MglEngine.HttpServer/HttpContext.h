#pragma once

#include "boost_deps.h"
#include "HttpResponse.h"

class HttpContext {
	bool _close;
	bool _processed;
	
	boost::asio::ip::tcp::socket& _socket;
	boost::beast::error_code _erc;
public:
	bool shouldClose() { return _close; }
	HttpContext(boost::asio::ip::tcp::socket& s, http::request<http::string_body>& r)
		:_socket(s), request(r) {
		_processed = false;
	}

	http::request<http::string_body>& request;

	bool isRequestProcessed() { return _processed; }

	std::string httpMethod() {
		
		switch (request.method())
		{
		case http::verb::get:
			return "GET";
		case http::verb::post:
			return "POST";
		case http::verb::put:
			return "PUT";
		case http::verb::delete_:
			return "DELETE";
		default:
			return "SomethingElse";
		}
	}
		
	http::response<http::string_body> Http500(std::string error)
	{
		auto res = http::response<http::string_body>(http::status::internal_server_error, request.version());
		res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
		res.keep_alive(request.keep_alive());
		res.set(http::field::content_type, "text/html");
		res.body() = error;
		res.prepare_payload();
		return res;
	}

	http::response<http::string_body> Http400(std::string error)
	{
		auto res = http::response<http::string_body>(http::status::not_found, request.version());
		res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
		res.keep_alive(request.keep_alive());
		res.set(http::field::content_type, "text/html");
		res.body() = error;
		res.prepare_payload();
		return res;
	}
	

	void send(HttpResponse&& msg)
	{
		if (_processed)
			throw std::exception("Trying to send request twice");
		_close = msg.need_eof();
		_processed = true;
		http::serializer<false, http::string_body> sr{ msg };
		http::write(_socket, sr, _erc);
	}

};
