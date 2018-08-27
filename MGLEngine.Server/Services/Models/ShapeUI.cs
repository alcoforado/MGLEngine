using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MGLEngineCLR;
using Newtonsoft.Json;

namespace MGLEngine.Server.Services.Models
{
    public class ShapeUI
    {
        public String Id { get; set; }
        public string Name { get; set; }

        public String TopologyTypeName { get; set; }
        public String RenderTypeName { get; set; }
        public Object Topology { get ; set; }
        public Object Render { get; set; }

        [JsonIgnore]
        public ShapeHandle Handle { get; set; }

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
