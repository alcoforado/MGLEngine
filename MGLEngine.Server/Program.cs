using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
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
            w.PsychoRun();
        }
    }
}
