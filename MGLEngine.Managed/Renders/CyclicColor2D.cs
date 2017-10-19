using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GlmNet;

namespace MGLEngine.Managed.Renders
{
    public class CyclicColor2D:IRender2D
    {
        public List<GlmNet.vec3> Colors { get; set; }

        public CyclicColor2D()
        {
            Colors = new List<vec3>();
        }
    }
}
