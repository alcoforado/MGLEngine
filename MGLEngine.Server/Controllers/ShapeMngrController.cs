using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Web.Http;
using MGLEngine.Server.Models;
using MGLEngine.Server.Services.Interfaces;
using MGLEngine.Server.Services.Models;
using MUtils.Reflection;
using Newtonsoft.Json;
using TestApp.Services.Interfaces;
using TestApp.WebApi.Models.ShapeMngr;

namespace TestApp.WebApi.Controllers
{
    public class ShapeMngrController : ApiController
    {
        
        private int _idCounter = 0;
       // private IShapesMngrMapper _mapper;
        private IShapeMngrService _mngrService;

        private readonly IViewModelMapperService _mapper;

        public List<string> GetTopologies()
        {
            return (
                from x in _mngrService.GetShapeTypes()
                select x.Key
                ).ToList(); ;
        }


        public ShapeMngrController(IShapeMngrService mngrService,IViewModelMapperService mapper)
        {
            _mngrService = mngrService;
            _mapper = mapper;
        }

        [HttpGet]
        public List<TypeViewModel> ShapeTypes()
        {
            return _mngrService.GetShapeTypes().Select(pair => _mapper.ToUITypeDto(pair.Key, pair.Value)).ToList();
        }

        [HttpGet]
        public List<TypeViewModel> RenderTypes()
        {
            return _mngrService.GetRenderTypes().Select(pair => _mapper.ToUITypeDto(pair.Key, pair.Value)).ToList();
        }


        [HttpPost]
        [Route("api/shapemngr/shape/{typeId}")]
        public CreateShapeViewModel Shape(string typeId)
        {
            var shape = _mngrService.CreateShape(typeId);
            return new CreateShapeViewModel(shape);
        }
        /*
        [HttpPost]
        public void UpdateShape(UpdateShapeViewModel model)
        {
            ShapeUI shape = _mngrService.GetShape(model.Id);
            if (shape == null)
            {
                throw new Exception($"Shape {model.Id} {model.Name} not found");
            }
            if (shape.IsDrawn())
            {
                shape.Dispose();
            }
            shape.Topology = _mngrService.CreateTopology(model.TopologyType);
            shape.Render = _mngrService.CreateRender(model.RenderType);
            JsonConvert.PopulateObject(model.TopologyJsonData, shape.Topology);
            JsonConvert.PopulateObject(model.RenderJsonData, shape.Render);
            
            if (String.IsNullOrWhiteSpace(modelRenderId))
            {
                _mngrService.SetShapeRender(model.ShapeId, null);
            }
            else
            {
                var render = _mngrService.GetRender(model.RenderId);
                _mngrService.SetShapeRender(model.ShapeId, render.Value);
            }
        }


        /*

        [HttpGet]
        public List<CreateShapeViewModel> Shapes()
        {
            return _mngrService.GetShapes().Select(x => new CreateShapeViewModel()
            {
                TypeName = x.Value.GetShapeName(),
                ShapeData = x.Value
            }).ToList();
        }

        [HttpGet]
        public List<RenderBase> Renders()
        {
            return _mngrService.GetRenders();
        } 



        [HttpGet]
        public void DeleteShape(string shapeId)
        {
            _mngrService.DeleteShape(shapeId);
        }

        

        [HttpPost]
        public void UpdateRender(UpdateRenderViewModel model)
        {
            RenderBase render = _mngrService.GetRender(model.RenderId).Value;
            JsonConvert.PopulateObject(model.RenderJsonData, render);
            _mngrService.RenderChanged(render);
        }

        

        [HttpPut]
        public RenderViewModel CreateRender(string renderTypeId)
        {
            var render = _mngrService.CreateRender(renderTypeId);

            return new RenderViewModel()
            {
                TypeName = renderTypeId,
                RenderData = render
                
            };
        }
        */

    }
}
