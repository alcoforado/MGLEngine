using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Web.Http;
using MGLEngine.Server.Services.Interfaces;
using MGLEngine.Server.Services.Models;
using MUtils.Reflection;


namespace MGLEngine.Server.Services
{
    public class ShapeMngrService : IShapeMngrService
    {
        private Dictionary<string, Type> _shapeTypes;
        private Dictionary<string, Type> _renderTypes;

        private int _idCounter = 0;
        private Dictionary<string, ShapeUI> _shapeCollection;
       
        public ShapeMngrService()
        {
            _shapeCollection = new Dictionary<string, ShapeUI>();
            _shapeTypes = new Dictionary<string, Type>();
            _renderTypes = new Dictionary<string, Type>();

            var assembly = Assembly.Load(new AssemblyName("MGLEngine.CLR"));


            var shapesT = assembly.GetTypesInNamespace("MGLEngineCLR.Models.Topologies");
            foreach (var type in shapesT)
            {
                _shapeTypes.Add(type.Name, type);
            }

            
            
            
        }
        /*
        public RenderBase CreateRender(string renderType)
        {
            var result = (RenderBase)Activator.CreateInstance(_renderTypes[renderType]);
            _renderCollection.Add(result.Id,result);
            return result;
        }
        */




        public Dictionary<string, Type> GetShapeTypes()
        {
            return _shapeTypes;
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

        //public List<RenderBase> GetRenders()
        //{
        //    return _renderCollection.Select(x => x.Value).ToList();
        //}



       

       

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

        public ShapeUIBase CreateShape(string shapeTypeId)
        {
            if (!_shapeTypes.ContainsKey(shapeTypeId))
            {
                throw new Exception(String.Format("Error, type {0} not identified", shapeTypeId));
            }

            var shape = (ShapeUIBase)Activator.CreateInstance(_shapeTypes[shapeTypeId]);
            var render = new SolidColorRender() { Color = SharpDX.Color.Aquamarine };

            shape.SetRender(_dx,render);
            shape.Id= 
            shape.Name = "Shape" + Interlocked.Increment(ref _idCounter).ToString();
            _shapeCollection.Add(shape.Id, shape);
            return shape;
        }
        */
    }
}

