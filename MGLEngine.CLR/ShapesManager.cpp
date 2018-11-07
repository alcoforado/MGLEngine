#include <MGLEngine.Shared/ShapesService/ShapesService.h>
#include "ShapesManager.h"
#include <msclr\marshal_cppstd.h>

using namespace MGLEngineCLR;
using namespace System;
using namespace System::Collections::Generic;
MGLEngineCLR::ShapesManager::ShapesManager(Window^ w)
{
	_sh = new ShapesService(w->GetNativeHandle());
}





MGLEngineCLR::ShapesManager::~ShapesManager()
{
	delete _sh;
}

System::String ^ MGLEngineCLR::ShapesManager::CreateShape(String ^ topologyType, String ^ renderType)
{
	std::string arg1 = msclr::interop::marshal_as<std::string>(topologyType);
	std::string arg2 = msclr::interop::marshal_as<std::string>(renderType);

	std::string result = _sh->CreateShape(arg1, arg2);

	return gcnew String(result.c_str());

}

void MGLEngineCLR::ShapesManager::UpdateShape(int shapeId, String ^ shapeJson)
{
	std::string jj = msclr::interop::marshal_as<std::string>(shapeJson);
	return _sh->UpdateShape(shapeId, jj);
}

void MGLEngineCLR::ShapesManager::DeleteShape(int shapeId)
{
	_sh->DeleteShape(shapeId);
}

List<RenderType^>^ MGLEngineCLR::ShapesManager::GetRenderTypes()
{
	List<RenderType^>^ result = gcnew List<RenderType^>();

	for (auto pair=_sh->GetPainters2D().cbegin();pair != _sh->GetPainters2D().cend();pair++)
	{
		RenderType ^r = gcnew RenderType();
		r->Dim = 2;
		r->Name = gcnew String(pair->first.c_str());
		result->Add(r);
	}
	return result;

}



List<ShapeType^>^ MGLEngineCLR::ShapesManager::GetShapeTypes()
{
	List<ShapeType^>^ result = gcnew List<ShapeType^>();

	for (auto pair = _sh->GetShapes2D().cbegin(); pair != _sh->GetShapes2D().cend(); pair++)
	{
		ShapeType ^r = gcnew ShapeType();
		r->Dim = 2;
		r->Name = gcnew String(pair->first.c_str());
		result->Add(r);
	}
	return result;

	
}





