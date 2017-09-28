﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Web.Http;
using MGLEngine.Server.Models;
using MGLEngine.Server.Services.Interfaces;
using MUtils.Reflection;
using Newtonsoft.Json;
using TestApp.Services.Interfaces;

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
        /*

        [HttpGet]
        public List<ShapeViewModel> Shapes()
        {
            return _mngrService.GetShapes().Select(x => new ShapeViewModel()
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
        public void UpdateShape(UpdateShapeViewModel model)
        {
            ShapeUIBase shape = _mngrService.GetShape(model.ShapeId);
            JsonConvert.PopulateObject(model.ShapeJsonData, shape);
            if (String.IsNullOrWhiteSpace(model.RenderId))
            {
                _mngrService.SetShapeRender(model.ShapeId, null);
            }
            else
            {
                var render = _mngrService.GetRender(model.RenderId);
                _mngrService.SetShapeRender(model.ShapeId, render.Value);
            }
        }

        [HttpPost]
        public void UpdateRender(UpdateRenderViewModel model)
        {
            RenderBase render = _mngrService.GetRender(model.RenderId).Value;
            JsonConvert.PopulateObject(model.RenderJsonData, render);
            _mngrService.RenderChanged(render);
        }

        [HttpPut]
        public ShapeViewModel CreateShape(string shapeTypeId)
        {
            var shape=_mngrService.CreateShape(shapeTypeId);
        
            return new ShapeViewModel()
            {
                TypeName = shapeTypeId,
                ShapeData = shape,
                RenderId = null
            };
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
