#pragma once
#using "NetLibs/GlmNet.dll"
using namespace GlmNet;
using namespace System::Collections::Generic;

namespace MGLEngineCLR
{
	namespace Models {
		namespace Renders {
			public ref class CyclicColor
			{
			public:
				List<vec3> Colors;
				void Render(Object^ Topology);
			};
		}
	}
}
