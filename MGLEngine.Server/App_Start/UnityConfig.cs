using Microsoft.Practices.Unity;
using System.Web.Http;
using MGLEngine.Server.Services.Interfaces;
using Unity.WebApi;
using MGLEngine.Server.Services;
using MGLEngineCLR;
namespace MGLEngine.Server
{
    public static class UnityConfig
    {
        static public void Config(IUnityContainer container)
        {
            container.RegisterType<IShapeMngrService, ShapeMngrService>(new ContainerControlledLifetimeManager());
            container.RegisterType<ShapesManager>(new ContainerControlledLifetimeManager());

            container.RegisterType<IViewModelMapperService, ViewModelMapperService>();

        }
    }
}