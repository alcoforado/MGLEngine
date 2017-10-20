#pragma once
#include "BasicTypesMapper.h"
using namespace MGLEngine::Managed::Topologies;
using namespace System::Collections::Generic;
using namespace System;
using namespace System::Reflection;

class ITopology2D;

namespace MGLEngineCLR {
	ref class Topology2DMapper : BasicTypesMapper
	{
		static Dictionary<String^, MethodInfo^> ^dictionary = gcnew Dictionary<String^, MethodInfo^>();

	public:

		Topology2DMapper();
		~Topology2DMapper();

		ITopology2D* Map(MGLEngine::Managed::Topologies::IMngTopology2D^  obj);

		ITopology2D* Convert(MGLEngine::Managed::Topologies::Triangle2D^ obj);


	};


}
