#include <MGLEngine.Shared/Resources/ResourceManager.h>
#include <MGLEngine.Shared/Interfaces/IGraphicLibrary.h>
#include <MGLEngine.Shared/Utils/eassert.h>

ResourceManager::ResourceManager(IGraphicLibrary& gl, std::string basePath)
	:_gl(gl),_base_path(basePath)
{

}

std::string ResourceManager::GetFullPath(std::string relPath)
{
	if (_base_path.empty())
		return relPath;
	else
		return (_base_path / std::filesystem::path(relPath)).string();
}

void ResourceManager::RegisterShaderBindings(ShaderContext& shader)
{
	auto& shaderConfig = shader.GetConfiguration();
	for (auto& samplerConfig : shaderConfig.samplers)
	{
		_pGlobalBindingsTable->AddSampler2D(samplerConfig.binding, samplerConfig.name, shader.GetName());
	}
	if (shaderConfig.pushConstant.Defined())
	{
		_pGlobalBindingsTable->AddPushConstant(shaderConfig.pushConstant,shader.GetName());

	}
	for (auto& ubo : shaderConfig.ubos)
	{
		_pGlobalBindingsTable->AddUbo(ubo, shader.GetName());
	}
	
}

void ResourceManager::RegisterShapeResources(ShaderContext &shader)
{
	int i = 1;
	
	for (auto& shape : shader.GetDrawingElements())
	{
		ShaderRef ref;
		ref.name = std::format("Shader {}, Shape {}", shader.GetName(), i);
		ref.index = shader.GetIndex();
		for (auto& resourceConfig : shape.config.GetResourceDeclarations())
		{
			_pGlobalBindingsTable->AssignImageResource(resourceConfig.samplerName, resourceConfig, ref);

		}
		i++;
	}
}

const FontAtlasMetadata& ResourceManager::GetFontMetadata(std::string sampleName) const 
{
	auto globalIndex = _pGlobalBindingsTable->GetResourceByName(sampleName);
	eassert(globalIndex.IsSampler(), std::format("Resource {} is not a sampler", sampleName));
	
	
	auto sampler=_pGlobalBindingsTable->GetSampler(sampleName);
	eassert(!sampler.resources.empty() && sampler.resources.front().config.IsFont(), "Sampler does not have a font");
	auto fontId = sampler.resources.front().MetadataId;
	eassert(fontId < vFontAtlas.size(), "Invalid Metadata Id");
	
	return vFontAtlas[fontId]->metadata;
}

void ResourceManager::LoadAllResources()
{

	for (auto& sampler2D : _pGlobalBindingsTable->GetSampler2DBindings())
	{

		if (sampler2D.resources.size() == 1)
		{
			auto res = this->Load(sampler2D.resources[0]);
			sampler2D.resources[0].glId = res.glid;
			sampler2D.resources[0].MetadataId = res.MetadataId;
		}


	}

	for (auto& ubo : _pGlobalBindingsTable->GetUboBindings())
	{
		ubo.glId = _gl.CreateUbo(ubo.binding, ubo.sizeOfDataType,ubo.initValue);
	}
};




Resource ResourceManager::Load(ResourceRef& resRef)
{
	ITexImage texImage;
	switch (resRef.config.type)
	{
		case ResourceType::IMAGE:
		{
			auto img = _imgLoader.LoadAsRGBA(GetFullPath(resRef.config.filePath));
			auto glId=_gl.LoadTexture(*img);
			return Resource{
				.glid = glId,
				.MetadataId = 0
			};
		}
		case ResourceType::FREE_TYPE_FONT:
		{
			
			auto atlas = _freeTypeLoader.Load(GetFullPath(resRef.config.filePath), resRef.config.GetFontData().PixelHeight, {}, 256);
			auto glId = _gl.LoadTexture(atlas->image);
			atlas->DisposeBitmap();
			vFontAtlas.push_back(atlas);
			return Resource{
				.glid = glId,
				.MetadataId = vFontAtlas.size() - 1
			};
		}

	}
	return Resource();
}



