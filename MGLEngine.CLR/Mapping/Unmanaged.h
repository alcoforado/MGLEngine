#pragma once
using namespace System::Runtime::InteropServices;
#using "NetLibs/GlmNet.dll"

namespace glm {}
using namespace ::glm;
#include <glm/detail/type_vec2.hpp>


namespace MGLEngineCLR
{
	namespace Mapping
	{
		class Unmanaged
		{
		public:
			static glm::vec2 Convert(GlmNet::vec2^ v2)
			{
				return glm::vec2(v2->x, v2->y);
			}



		};
	}
}