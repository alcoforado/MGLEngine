#include "ShaderBindingManager.h"
#include "GlobalBindingsTable.h"
ShaderBindingManager::ShaderBindingManager(const ShaderConfiguration &config,s_ptr<GlobalBindingsTable> pGlobalTable)
	:_pGlobalTable(pGlobalTable)
{
	_totalStride = 0;
	for (auto& v : config.vertexAttributes)
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

	for (auto& samplerConfig : config.samplers)
	{
		_pGlobalTable->AddSampler2D(samplerConfig.binding, samplerConfig.name,config.name);
	}


}
