#include <MGLEngine.Shared/Interfaces/IShader.h>
#include <stdint.h>
#include <MGLEngine.Shared/Shaders/Texture2D/texture2D_frag.h>
#include <MGLEngine.Shared/Shaders/Texture2D/texture2D_vert.h>

#include<string>

class Texture2D : public IShader {
	public:
		inline static std::string name="Texture2D";
		virtual void Init(IShaderConfiguration& config) override
		{
			config.DeclareVertexAttribute_FloatVec4("text", 1);
			config.DeclareVertexAttribute_FloatVec2("position2d", 0);
			config.SetVerticeShader(texture2D_vert,  sizeof(texture2D_vert));
			config.SetFragmentShader(texture2D_frag, sizeof(texture2D_frag));
		}
		
};