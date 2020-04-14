#pragma once

class HttpServer;


class IController {

public:
	virtual void RegisterRoutes(HttpServer* pServer) = 0;

};