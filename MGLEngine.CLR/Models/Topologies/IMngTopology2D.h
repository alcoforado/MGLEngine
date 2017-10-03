#pragma once

class ITopology2D;


namespace MGLEngineCLR {
	namespace Models {
		namespace Topologies {
			interface class IMngTopology2D
			{
			public:
				ITopology2D* ToUnmanaged();
			};
		}
	}
}



