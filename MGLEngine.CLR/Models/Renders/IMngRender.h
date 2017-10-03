#pragma once

class ITopology2D;
class ShaderCollection;

namespace MGLEngineCLR {
	namespace Models {
		namespace Renders {
			interface class IMngRender
			{
			public:
				void Render(Object^ topology, MngRenderContext^ context);
			};
		}
	}
}



