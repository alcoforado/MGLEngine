using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MGLEngine.Server.Services.Models
{
    public class ShapeUI
    {
        public String Id { get; set; }
        public string Name { get; set; }
        public Object Topology { get; set; }
        public Object Render { get; set; }

        public bool IsDrawn()
        {
            return Render != null;
        }

        public void Dispose()
        {
            throw new NotImplementedException();
        }
    }
}
