#include "WebApiMiddletier.h"
#include "WebApiContext.h"
#include "HttpResponses.h"
void WebApiMiddletier::Process(HttpContext& cntx)
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
			cntx.send(HttpResponses::Http500(e.what(), cntx.request.version(), cntx.request.keep_alive()));
			
		}
		
		


	}




}
