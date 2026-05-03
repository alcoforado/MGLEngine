#include <MGLEngine.Shared/Interfaces/IShader.h>
#include <stdint.h>
#include <MGLEngine.Shared/Shaders/Color2D/color2d_vert.h>
#include <MGLEngine.Shared/Shaders/Color2D/color2d_frag.h>
#include<string>

class ShaderColor2D : public IShader {
	public:
		inline static std::string name="ShaderColor2D";
		virtual void Init(IShaderConfiguration& config) override;
		
};