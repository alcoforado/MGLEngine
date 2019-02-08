using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Web.Http;
using MGLEngineCLR;
namespace MGLEngine.Server.Controllers
{
    public class ShapeController : ApiController
    {
        private ShapesManager _mngr;

        public ShapeController(ShapesManager mngr)
        {
            _mngr = mngr;
        }


        [HttpGet]
        public List<ShapeType> ShapeTypes()
        {
            return _mngr.GetShapeTypes();
        }

        [HttpGet]
        public List<RenderType> RenderTypes()
        {
            return _mngr.GetRenderTypes();
        }

       





    }
}
