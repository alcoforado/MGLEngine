#include "BindingManager.h"
BindingManager::BindingManager(std::vector<VertexAttributeDeclaration> vAttribs)
{
	_totalStride = 0;
	for (auto& v : vAttribs)
	{
		VertexAttribute elem = {
			.name = v.name,
			.location = v.location,
			.type = v.type
		};
		elem.offset = _totalStride;
		
		elem.size = FieldTypeInfo::sizeOfType(elem.type);
		_totalStride += elem.size;
		_verticeData.push_back(elem);
	}
}
