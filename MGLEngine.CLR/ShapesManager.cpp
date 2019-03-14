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

System::String ^ MGLEngineCLR::ShapesManager::SaveShape(String ^shapeJson)
{
	std::string arg1 = msclr::interop::marshal_as<std::string>(shapeJson);

	std::string result = _sh->SaveShape(arg1);

	return gcnew String(result.c_str());

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





