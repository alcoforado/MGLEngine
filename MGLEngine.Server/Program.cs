﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using MGLEngineCLR;
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
            var w = new Window();
            w.SetSize(500, 700);
            w.PsychoRun();
        }
    }
}
