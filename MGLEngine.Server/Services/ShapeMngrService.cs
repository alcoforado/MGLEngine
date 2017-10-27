using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Web.Http;
using MGLEngine.Managed.Renders;
using MGLEngine.Managed.Topologies;
using MGLEngine.Server.Services.Interfaces;
using MGLEngine.Server.Services.Models;
using MUtils.Reflection;


namespace MGLEngine.Server.Services
{
    public class ShapeMngrService : IShapeMngrService
    {
        private Dictionary<string, Type> _topologyTypes;
        private Dictionary<string, Type> _renderTypes;

        private int _idCounter = 0;
        private Dictionary<string, ShapeUI> _shapeCollection;
       
        public ShapeMngrService()
        {
            _shapeCollection = new Dictionary<string, ShapeUI>();
            _topologyTypes = new Dictionary<string, Type>();
            _renderTypes = new Dictionary<string, Type>();

            var assembly = Assembly.Load(new AssemblyName("MGLEngine.Managed"));


            var shapesT = typeof(IMngTopology2D).GetImplementationsInAssembly(assembly);
            foreach (var type in shapesT)
            {
                _topologyTypes.Add(type.Name, type);
            }

            var rendersT = typeof(IRender2D).GetImplementationsInAssembly(assembly);
            foreach (var type in rendersT)
            {
                _renderTypes.Add(type.Name, type);
            }


        }
        
        //public RenderBase CreateRender(string renderType)
        //{
        //    var result = (RenderBase)Activator.CreateInstance(_renderTypes[renderType]);
        //    _renderCollection.Add(result.Id,result);
        //    return result;
        //}
        




        public Dictionary<string, Type> GetShapeTypes()
        {
            return _topologyTypes;
        }

        public Dictionary<string, Type> GetRenderTypes()
        {
            return _renderTypes;
        }
        public ShapeUI GetShape(string id)
        {
            return _shapeCollection[id];
        }

        public Dictionary<string, ShapeUI> GetShapes()
        {
            return _shapeCollection;
        }

        public void UpdateShape(ShapeUI shape)
        {
            if (String.IsNullOrEmpty(shape.Id))
            {
                throw new Exception("Invalid Id");
            }
            if (shape.Render == null)
            {
                throw new Exception("No Render provided");
            }
            if (shape.Topology == null)
            {
                throw new Exception("No Topology Provided");
            }
           
        }



       

       

        public bool HasShape(string shapeId)
        {
            return _shapeCollection.ContainsKey(shapeId);
        }

        /*

          public void DeleteShape(string id)
          {
              if (!_shapeCollection.ContainsKey(id))
              {
                  throw new Exception(String.Format("Error, Shape Id {0} not found", id));
              }
              else
              {
                  var shape = _shapeCollection[id];
                  shape.DetachFromShader(_dx);
                  _shapeCollection.Remove(id);
              }

          }
          */

        /// <summary>
        /// Create a shape with a specific topology with blank fields and no render
        /// In this incomplete state the shape cannot be rendered and is not sent to 
        /// the shaders. The user needs to update with valid values in order to be able
        /// to draw it.
        /// </summary>
        /// <param name="topologyTypeId"></param>
        /// <returns></returns>
        public ShapeUI CreateShape(string topologyTypeId)
        {
            if (!_topologyTypes.ContainsKey(topologyTypeId))
            {
                throw new Exception(String.Format("Error, type {0} not identified", topologyTypeId));
            }

            var result = new ShapeUI();
            result.Topology = (Object) Activator.CreateInstance(_topologyTypes[topologyTypeId]);
            result.Render = null;
            result.Id = new Guid().ToString();
            result.Name = "Shape" + Interlocked.Increment(ref _idCounter).ToString();
            _shapeCollection.Add(result.Id.ToString(), result);
            return result;
        }

        public object CreateRender(string modelRenderType)
        {
            if (!_renderTypes.ContainsKey(modelRenderType))
            {
                throw new Exception(String.Format("Error, Render type {0} not identified", modelRenderType));
            }
           return (Object)Activator.CreateInstance(_renderTypes[modelRenderType]);

        }
    }
}

