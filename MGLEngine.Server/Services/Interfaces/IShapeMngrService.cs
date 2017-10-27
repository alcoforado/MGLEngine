using System;
using System.Collections.Generic;
using MGLEngine.Server.Services.Models;

namespace MGLEngine.Server.Services.Interfaces
{
    public interface IShapeMngrService
    {
        Dictionary<string, Type> GetShapeTypes();
        Dictionary<string, Type> GetRenderTypes();
        ShapeUI GetShape(string id);
        Dictionary<string, ShapeUI> GetShapes();
        bool HasShape(string shapeId);

        /// <summary>
        /// Create a shape with a specific topology with blank fields and no render
        /// In this incomplete state the shape cannot be rendered and is not sent to 
        /// the shaders. The user needs to update with valid values in order to be able
        /// to draw it.
        /// </summary>
        /// <param name="topologyTypeId"></param>
        /// <returns></returns>
        ShapeUI CreateShape(string topologyTypeId);


        object CreateRender(string modelRenderType);
    }
}
