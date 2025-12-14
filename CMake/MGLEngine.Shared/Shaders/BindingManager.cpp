#include "BindingManager.h"
BindingManager::BindingManager(std::vector<VertexAttributeDeclaration> vAttribs)
{
	size_t offset = 0;
	for (auto& v : vAttribs)
	{
		VertexAttribute elem = {
			.name = v.name,
			.location = v.location,
			.type = v.type
		};
		elem.offset = offset;
		//offset+=FieldTypeInfo::Size(elem.type)
		_verticeData.push_back(elem);
	}
	totalStride = offset;
}
