#pragma once

class ITopology3D;
namespace MGLEngineCLR {
	namespace Models {
		namespace Topologies {
			interface class IMngTopology3D
			{
			public:
				ITopology3D* ToUnmanaged();
			};
		}
	}
}

