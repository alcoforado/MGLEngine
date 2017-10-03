#include "Topologies2D.h"
#include "../../Mapping/Unmanaged.h"
#include <Topologies/Triangle2D.h>

using namespace MGLEngineCLR::Mapping;

namespace MGLEngineCLR {
	namespace Models {
		namespace Topologies {
			ITopology2D* Triangle2D::ToUnmanaged()
			{
				return new ::Triangle2D(
					Unmanaged::Convert(this->P1),
					Unmanaged::Convert(this->P2),
					Unmanaged::Convert(this->P3));
			}
		}
	}
}