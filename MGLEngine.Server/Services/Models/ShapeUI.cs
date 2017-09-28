using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MGLEngine.Server.Services.Models
{
    public class ShapeUI
    {
        public Guid Id { get; set; }
        public string Name { get; set; }
        public Object Topology { get; set; }
        public Object Painter { get; set; }

    }
}
