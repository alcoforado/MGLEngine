#include "ShapeHandle.h"
#include <MGLEngine.Shared\Shaders\IShader.h>

using System::Exception;

void ShapeHandle::Delete()
{
	if (_shapeHandle != nullptr)
		_shapeHandle->Delete();
	else
		throw gcnew Exception("Shape Handle tried to be deleted twice;");
	_shapeHandle = nullptr;
}

