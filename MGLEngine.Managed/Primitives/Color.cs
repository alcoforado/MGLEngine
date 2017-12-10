using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GlmNet;

namespace MGLEngine.Managed.Primitives
{
    public class Color
    {
        public  float R { get; set; }
        public  float G { get; set; }
        public  float B { get; set; }
        public float Alpha { get; set; }
        public Color()
        {
            R = G = B = 0;
        }

        public vec3 toVec3()
        {
            return new vec3(R, G, B);
        }
    }
}
