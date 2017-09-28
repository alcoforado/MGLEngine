#pragma once
using namespace System::Runtime::InteropServices;
#using "NetLibs/GlmNet.dll"
using namespace GlmNet;


namespace MGLEngineCLR {
	namespace Model {
		namespace Topologies {
			public value struct Triangle2D
			{
				vec2 P1;
				vec2 P2;
				vec2 P3;
			};


		}
	}
}
