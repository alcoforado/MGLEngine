#include "PhongLight.h"
#include "phongLight_frag.h"
#include "phongLight_vert.h"


class PhongLightSahder :IShader {
public:
	//ShaderConfiguration
	virtual void Init(ShaderConfiguration& config)
	{
		config.EnableCulling(true);
		config.DeclareVertexAttribute_FloatVec3("position3d", 0);
		config.DeclareVertexAttribute_FloatVec3("normal", 1);
		config.SetVerticeShader(phongLight_vert, sizeof(phongLight_vert));
		config.SetFragmentShader(phongLight_frag, sizeof(phongLight_frag));
		glm::mat4 m(1);
		config.DeclareUbo(UboBindingCollection::CameraTransform, Std140Mat4(m));
		config.DeclareUbo(UboBindingCollection::LightArray,Std140Light)
	}

};

