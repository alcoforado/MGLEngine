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
            TopologyTypeName = shape.Topology.GetType().Name;
            ShapeData = shape.Topology;
            RenderTypeName = shape.Render?.GetType().Name ?? "";
            RenderData = shape.Render;
        }


        public string Name { get; set; }
        public string Id { get; set; }
        public string TopologyTypeName { get; set; }
        public Object ShapeData { get; set; }
        public Object RenderData { get; set; }
        public string RenderTypeName { get; set; }
    }
}
