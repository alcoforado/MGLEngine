#include "WebApiMiddletier.h"
#include "WebApiContext.h"
#include "HttpResponse.h"
void WebApiMiddleware::process(HttpContext& cntx)
{
	auto requestUrl = cntx.request.target().to_string();
	Url rUrl(requestUrl);
	auto match = RouteTable.MatchRoute(rUrl, cntx.httpMethod());

	if (match != NULL)
	{
		WebApiContext apiCtx(cntx,match->RouteParameters);
		
		try {
			cntx.send(match->handlerFunction(apiCtx));
		}
		catch (const std::exception& e) {
			cntx.send(HttpResponse::Http500(e.what(), cntx.request.version(), cntx.request.keep_alive()));
			
		}
		
		


	}




}
