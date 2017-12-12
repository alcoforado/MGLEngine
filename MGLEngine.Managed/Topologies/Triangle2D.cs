using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GlmNet;

namespace MGLEngine.Managed.Topologies
{
    public  class Triangle2D : IMngTopology2D
    {
        public vec2 P1 { get; set; }
        public vec2 P2 { get; set; }
        public vec2 P3 { get; set; }

        public void Validate()
        {
        }
    }
}
