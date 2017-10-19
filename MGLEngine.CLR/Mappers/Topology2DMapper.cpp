#include "Topology2DMapper.h"

#include <MGLEngine.Shared\Topologies\Triangle2D.h>
using namespace MGLEngine::Managed::Topologies;
using namespace System::Threading;
using namespace System;
Topology2DMapper::Topology2DMapper()
{
	if (this->dictionary->Count  == 0)
	{
		Monitor::Enter(this->dictionary);
		for each (auto f in this->GetType()->GetMethods())
		{
			if (f->Name == "Convert")
			{
				this->dictionary->default[f->GetParameters()[0]->ParameterType->Name]=f;
				
			}
		}
		Monitor::Exit(this->dictionary);


	}
}


Topology2DMapper::~Topology2DMapper()
{
}

ITopology2D * Topology2DMapper::Map(MGLEngine::Managed::Topologies::IMngTopology2D^ obj)
{

	auto f = this->dictionary->default[obj->GetType()->Name];
	array<Object^> ^parameters = { obj };
	auto result = f->Invoke(this, parameters);
	auto rst = dynamic_cast<Pointer^>(result);
	void *tt = (Pointer::Unbox(rst));
	return static_cast<ITopology2D*>(tt);
}


ITopology2D* Topology2DMapper::Convert(MGLEngine::Managed::Topologies::Triangle2D^ obj)
{
	auto result =  new ::Triangle2D(Map(obj->P1),Map(obj->P2),Map(obj->P3));
	return result;
}



