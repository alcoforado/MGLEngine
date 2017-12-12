using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GlmNet;
using MGLEngine.Managed.Primitives;

namespace MGLEngine.Managed.Renders
{
    public class CyclicColor2D:IRender2D
    {
        public List<Color> Colors { get; set; }

        public CyclicColor2D()
        {
            Colors = new List<Color>();
        }

        public void Validate()
        {
            if (Colors == null || Colors.Count==0)
            throw new Exception("Empty Color list supplied");
        }
    }
}
