using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestApp.WebApi.Models.ShapeMngr
{
    public class UpdateShapeViewModel
    {
        public string Id { get; set; }
        public string Name { get; set; }
        public string TopologyType { get; set; }
        public Object ShapeData { get; set; }
        public Object RenderData { get; set; }
        public string RenderType { get; set; }

    }
}
