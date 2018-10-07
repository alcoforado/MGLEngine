using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MGLEngineCLR;

namespace MGLEngine.Server.EventHandlers
{
    public class EditPathEventHandler : MGLEngineCLR.IMngWindowEventHandler
    {
        public void OnMouseMove(double x, double y)
        {
            System.Diagnostics.Debug.WriteLine($"Moved to {x} {y}");
        }

        public void OnMouseClick(MngClickEvent evt)
        {
        }
    }
}
