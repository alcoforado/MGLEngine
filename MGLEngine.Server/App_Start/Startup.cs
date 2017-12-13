using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http.Headers;
using System.Text;
using System.Threading.Tasks;
using System.Web.Http;
using System.Web.Http.ExceptionHandling;
using MGLEngine.Server;
using MGLEngine.Server.App_Start;
using Microsoft.Owin.FileSystems;
using Microsoft.Owin.StaticFiles;
using Microsoft.Practices.Unity;
using Owin;
using Unity.WebApi;

namespace TestApp.App_Config
{
    public class Startup
    {
        internal static IUnityContainer Container { get; set; }
        // This code configures Web API. The Startup class is specified as a type
        // parameter in the WebApp.Start method.
        public void Configuration(IAppBuilder appBuilder)
        {
            // Configure Web API for self-host. 
            HttpConfiguration config = new HttpConfiguration();
            config.MapHttpAttributeRoutes();

            config.Routes.MapHttpRoute(
                name: "DefaultApi",
                routeTemplate: "api/{controller}/{action}/{id}",
                defaults: new { action = "index", id = RouteParameter.Optional }
            );
            config.Formatters.JsonFormatter.SupportedMediaTypes
                .Add(new MediaTypeHeaderValue("text/html"));
            
            UnityConfig.Config(Container);

            config.DependencyResolver = new UnityDependencyResolver(Container);

            //error handler
            config.Services.Replace(typeof(IExceptionHandler), new GlobalErrorHandler());

            appBuilder.UseWebApi(config);

           


            var fileSystem = new PhysicalFileSystem("../../../content");
            var options = new FileServerOptions
            {
                EnableDirectoryBrowsing = true,
                FileSystem = fileSystem
            };

            appBuilder.UseFileServer(options);


        }
    }
}
