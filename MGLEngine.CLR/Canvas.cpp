#include "stdafx.h"
#include "Window.h"
#include "Canvas.h"
#include "Mappers/Topology2DMapper.h"
#include <MGLEngine.Shared\Renders\CyclicColor.h>
#include <MGLEngine.Shared\VerticeData\Color2D.h>
using namespace System::Threading;

namespace MGLEngineCLR {
	Canvas::Canvas(IMGLEngine *engine)
	{
		_mapper = gcnew MGLEngineCLR::Topology2DMapper();
		_engine = engine;
	}

	ShapeHandle^ Canvas::Render(IMngTopology2D^ topology, CyclicColor2D^ render)
	{
		ITopology2D* pTop = _mapper->Map(topology);
		auto colors = _mapper->MapList<Color^,glm::vec3>(render->Colors);
		auto pRender = new CyclicColor<Color2D>(colors);
		auto result = _engine->Color2DShader()->Add(pTop, pRender);
		return gcnew ShapeHandle(result);
	
	}

	Dictionary<String^, MethodInfo^>^ Canvas::GetReflectionDictionary()
	{
		if (this->dictionary->Count == 0)
		{
			Monitor::Enter(this->dictionary);
			if (this->dictionary->Count == 0)
			{
				for each (auto f in this->GetType()->GetMethods())
				{
					if (f->Name == "Render" && f->GetParameters()->Length == 2)
					{
						this->dictionary->default[f->GetParameters()[1]->ParameterType->Name] = f;
					}
				}
			}
			Monitor::Exit(this->dictionary);
		}
		return this->dictionary;
	}

	 ShapeHandle^ Canvas::Render(IMngTopology2D^ topology, IRender2D^ render)
	{
		auto dictionary = GetReflectionDictionary();
		if (!dictionary->ContainsKey(render->GetType()->Name))
		{
			throw gcnew Exception("No method Render(IMngTopology2D," + render->GetType()->Name + ") found in the Canvas class");
		}
		array<Object^> ^parameters = { topology,render};
		auto f = dictionary->default[render->GetType()->Name];
		auto result = f->Invoke(this, parameters);
		_engine->Redraw();
		return dynamic_cast<ShapeHandle^>(result);
	}

	


}