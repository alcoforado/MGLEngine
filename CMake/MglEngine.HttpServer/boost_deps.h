#pragma once
#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/config.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <memory.h>
namespace asio = boost::asio;
namespace http = boost::beast::http;

template<class T>
using s_ptr = std::shared_ptr<T>;



