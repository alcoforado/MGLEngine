using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using GlmNet;
using MGLEngine.Managed.Renders;
using MGLEngine.Managed.Topologies;
using MGLEngineCLR;
using Microsoft.Owin.Hosting;
using Microsoft.Practices.Unity;
using TestApp.App_Config;

namespace MGLEngine.Server
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            
            var Container = new UnityContainer();
            string baseAddress = "http://localhost:9000/";
            Startup.Container = Container;
            WebApp.Start<Startup>(url: baseAddress);
            var w = new Window();

            var tria = new Triangle2D();
            tria.P1 = new vec2(0,0);
            tria.P2 = new vec2(0,1);
            tria.P3 = new vec2(1, 1);

            var render = new CyclicColor2D();
            render.Colors.Add(new vec3(1.0f,1.0f,1.0f));



            w.GetCanvas().Render(tria,render);
            w.EasyRun();
        }
    }
}
