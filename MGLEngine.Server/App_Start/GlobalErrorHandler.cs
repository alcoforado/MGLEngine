using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http.Formatting;
using System.Net.Http.Headers;
using System.Runtime.Remoting.Messaging;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Web.Http.ExceptionHandling;
using System.Web.Http.Results;

namespace MGLEngine.Server.App_Start
{
    public class ErrorResult
    {
        public List<string> Errors = new List<string>();
    }

    public class GlobalErrorHandler : ExceptionHandler
    {
        public override void Handle(ExceptionHandlerContext context)
        {
            
            var errorResult = new ErrorResult();

            var ex = context.Exception;
            do
            {
                var userException = ex as UserException;
                if (userException != null)
                {
                    errorResult.Errors.AddRange(userException.Errors);
                }
                else
                {
                    errorResult.Errors.Add(context.Exception.Message);
                }
                ex = ex.InnerException;
            } while (ex != null);



            context.Result= new FormattedContentResult<ErrorResult>(
                HttpStatusCode.BadRequest,
                errorResult, 
                new JsonMediaTypeFormatter(), 
                new MediaTypeHeaderValue("application/json"),
                context.Request);
            //base.Handle(context);
        }

    }
}
