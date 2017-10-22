using Microsoft.Practices.Unity;
using System.Web.Http;
using MGLEngine.Server.Services.Interfaces;
using Unity.WebApi;
using MGLEngine.Server.Services;

namespace MGLEngine.Server
{
    public static class UnityConfig
    {
        static public void Config(IUnityContainer container)
        {
            container.RegisterType<IShapeMngrService, ShapeMngrService>();
            container.RegisterType<IViewModelMapperService, ViewModelMapperService>();

        }
    }
}