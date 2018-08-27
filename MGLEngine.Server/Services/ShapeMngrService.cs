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
using MGLEngine.Server.App_Start;
using MGLEngine.Server.Services.Interfaces;
using MGLEngine.Server.Services.Models;
using MGLEngineCLR;
using MUtils.Reflection;
using Newtonsoft.Json.Linq;


namespace MGLEngine.Server.Services
{
    public class ShapeMngrService : IShapeMngrService
    {
        private readonly Window _w;
        private Dictionary<string, Type> _topologyTypes;
        private Dictionary<string, Type> _renderTypes;

        private int _idCounter = 0;
        private Dictionary<string, ShapeUI> _shapeCollection;
        private JsonFileStore _store;
        public ShapeMngrService(Window w)
        {
            _w = w;
            _shapeCollection = new Dictionary<string, ShapeUI>();
            _topologyTypes = new Dictionary<string, Type>();
            _renderTypes = new Dictionary<string, Type>();
            _store = new JsonFileStore();
            _store.Open("objects.txt");

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

            LoadObjectsFromJson(_store.GetRoot());


        }

        private void LoadObjectsFromJson(JObject root)
        {

            var lst = _store.LoadIfExists<List<ShapeUI>>("shapes");

            if (lst != null)
            {
                foreach (ShapeUI sh in lst)
                {
                    _shapeCollection.Add(sh.Id,sh);
                    UpdateShape(sh.Id,sh.Topology,sh.Render);

                }


            }


        }

        //public RenderBase CreateRender(string renderType)
        //{
        //    var result = (RenderBase)Activator.CreateInstance(_renderTypes[renderType]);
        //    _renderCollection.Add(result.Id,result);
        //    return result;
        //}


        public void Redraw()
        {
          //  return _w.GetCanvas().
        }


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
            var result = new ShapeUI();
            result.Topology = (Object) CreateTopology(topologyTypeId);
            result.TopologyTypeName = topologyTypeId;
            result.Render = null;
            result.Id = Guid.NewGuid().ToString();
            result.Name = "Shape" + Interlocked.Increment(ref _idCounter).ToString();
            _shapeCollection.Add(result.Id, result);
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

        public object CreateTopology(string modelTopologyType)
        {
            if (!_topologyTypes.ContainsKey(modelTopologyType))
            {
                throw new Exception(String.Format("Error, Render type {0} not identified", modelTopologyType));
            }
            return (Object)Activator.CreateInstance(_topologyTypes[modelTopologyType]);
        }

        public void UpdateShape(string modelId, object topology, object render)
        {
            var render2d = render as IRender2D;
            var render3d = render as IRender3D;
            if (render2d != null)
            {
                IMngTopology2D top2D= topology as IMngTopology2D;
                if (top2D == null)
                    throw new Exception($"Shape of type {topology.GetType().Name} is not compatible to Render2D");
                List<string> errors = new List<string>();
                top2D.Validate(errors);
                render2d.Validate(errors);
                if (errors.Any())
                {
                    throw new UserException(errors);
                }
                ShapeUI shape = GetShapeUI(modelId);
                if (shape.Handle != null)
                    shape.Handle.Delete();
                shape.Handle=_w.GetCanvas().Render(top2D,render2d);
                shape.Render = render2d;
                shape.RenderTypeName = render2d.GetType().Name;
                shape.Topology = top2D;
                shape.TopologyTypeName = top2D.GetType().Name;
            }
            else if (render3d != null)
            {

            }
            else
            {
                throw new Exception("Render object is not IRender2D nor IRender3D");
            }
        }

        private ShapeUI GetShapeUI(string modelId)
        {
            if (!_shapeCollection.ContainsKey(modelId))
            {
                throw new Exception($"Shape {modelId} not found, make sure the shape is created  first");
            }
            return _shapeCollection[modelId];
        }

        ~ShapeMngrService()
        {
        //    _store.Save("shapes",_shapeCollection.ToList().Select(x=>x.Value).ToList());
        //   _store.Dispose();

        }

    }
}

