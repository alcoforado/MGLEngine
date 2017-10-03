#pragma once
using namespace System::Runtime::InteropServices;
#using "NetLibs/GlmNet.dll"

#include "IMngTopology2D.h"



namespace MGLEngineCLR {
	namespace Models {
		namespace Topologies {
			using GlmNet::vec2;
			using GlmNet::vec3;

			public value struct Triangle2D : public IMngTopology2D
			{
				vec2 P1;
				vec2 P2;
				vec2 P3;
			public:
				virtual ITopology2D* ToUnmanaged();
			};

			

		}
	}
}
