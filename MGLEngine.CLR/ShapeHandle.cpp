#include "ShapeHandle.h"
#include <MGLEngine.Shared\Shaders\IShader2D.h>

using System::Exception;
namespace MGLEngineCLR {
	void ShapeHandle::Delete()
	{
		if (_shapeHandle != nullptr)
			_shapeHandle->Delete();
		else
			throw gcnew Exception("Shape Handle tried to be deleted twice;");
		_shapeHandle = nullptr;
	}

}