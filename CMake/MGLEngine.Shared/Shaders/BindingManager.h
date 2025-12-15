#pragma once	
#include <string>
#include<map>
#include <vector>
#include <MGLEngine.Shared/Shaders/FieldType.h>
#include <MGLEngine.Shared/Utils/Arrays/InterleavedMemoryStream.h>

struct VertexAttribute {
	std::string name;
	uint32_t location;
	size_t size;
	size_t offset;
	FieldType type;

};
struct VertexAttributeDeclaration {
	std::string name;
	uint32_t location;
	FieldType type;
};


class BindingManager {
	std::vector<VertexAttribute> _verticeData;
	size_t totalStride=0;
public:
	BindingManager(std::vector<VertexAttributeDeclaration> vAttribs);
	BindingManager() { totalStride = 0; };
	size_t GetStride() { return totalStride; }
	const std::vector<VertexAttribute> GetVertexAttributes();
};
