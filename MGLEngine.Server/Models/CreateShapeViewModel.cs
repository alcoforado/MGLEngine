using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Emit;
using System.Text;
using System.Threading.Tasks;
using MGLEngine.Server.Services.Models;

namespace TestApp.WebApi.Models.ShapeMngr
{
    public class CreateShapeViewModel
    {
       

        public CreateShapeViewModel(ShapeUI shape)
        {
            Name = shape.Name;
            Id = shape.Id.ToString();
            TopologyType = shape.Topology.GetType().Name;
            ShapeData = shape.Topology;
            RenderType = shape.Painter?.GetType().Name ?? "";
            RenderData = shape.Painter;
        }


        public string Name { get; set; }
        public string Id { get; set; }
        public string TopologyType { get; set; }
        public Object ShapeData { get; set; }
        public Object RenderData { get; set; }
        public string RenderType { get; set; }
    }
}
