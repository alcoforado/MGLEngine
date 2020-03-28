#include "HttpServer.h"




void HttpServer::process_request(asio::ip::tcp::socket& socket)
{
	boost::beast::error_code erc;
	boost::beast::flat_buffer buffer;

	for (;;)
	{
		http::request<http::string_body> req;
		http::read(socket, buffer, req, erc);
		if (erc == http::error::end_of_stream)
			break;
		if (erc)
		{
			std::cout << "Server Error When Reading the request: " << erc.message() << std::endl;
			return;
		}
			
		



	}

}
HttpServer::HttpServer(int port)
	:_ioc(2),
	_host{ boost::asio::ip::make_address_v4("127.0.0.1"), static_cast<unsigned short>(port) }
{
}
	



void HttpServer::run()
{
	std::cout << "Listening at 127.0.0.1:" << _host.port() << std::endl;
	boost::asio::ip::tcp::acceptor acceptor(_ioc, _host);
	for (;;) {

		boost::asio::ip::tcp::socket socket(_ioc);
		acceptor.accept(socket);
			
		std::thread(std::bind(&HttpServer::process_request, this, std::move(socket))).detach();

	}

}
