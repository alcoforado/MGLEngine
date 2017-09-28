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
    }
}
