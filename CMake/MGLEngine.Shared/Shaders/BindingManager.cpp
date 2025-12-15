#include "BindingManager.h"
BindingManager::BindingManager(std::vector<VertexAttributeDeclaration> vAttribs)
{
	size_t _totalStride = 0;
	for (auto& v : vAttribs)
	{
		VertexAttribute elem = {
			.name = v.name,
			.location = v.location,
			.type = v.type
		};
		elem.offset = _totalStride;
		_totalStride += FieldTypeInfo::sizeOfType(elem.type);
		elem.size = _totalStride;
		
		_verticeData.push_back(elem);
	}
}
