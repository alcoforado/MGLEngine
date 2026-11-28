#include "PhongLight.h"
#include "phongLight_frag.h"
#include "phongLight_vert.h"


class PhongLightShader :IShader {
public:
	//ShaderConfiguration
	virtual void Init(ShaderConfiguration& config)
	{
		config.EnableCulling(true);
		config.DeclareVertexAttribute_FloatVec3("position3d", 0);
		config.DeclareVertexAttribute_FloatVec4("color", 1); 
		config.DeclareVertexAttribute_FloatVec3("normal", 2);
		config.SetVerticeShader(phongLight_vert, sizeof(phongLight_vert));
		config.SetFragmentShader(phongLight_frag, sizeof(phongLight_frag));
		glm::mat4 m(1);
		Std140Light light({ 10,10,10 }, { 0,0,0 }, { 1,1,1 }, 0.01);
		config.DeclareUbo(UboBindingCollection::CameraTransform, Std140Mat4(m));
		config.DeclareUbo(UboBindingCollection::Lights, light);
	}

};

PhongLight::PhongLight(MGLEngine& engine, IMesh3DWithNormals& mesh, const std::vector<glm::vec4>& colors)
	:_mesh(mesh),_colors(colors)
{
	engine.AddShape<PhongLightShader>(*this);
}

 void PhongLight::RenderData(RenderSerializationContext& context)
{
	 auto& colorStream = context.GetVerticeAttribute("color");
	 auto& posStream = context.GetVerticeAttribute("position3d");
	 auto& normalStream = context.GetVerticeAttribute("normal");
	 auto& indexStream = context.GetIndicesStream();
	 _mesh.RenderMesh(posStream, indexStream,normalStream);


	 auto nVertices = _mesh.NVertices();
	 //Fill colors in a round-robin fashion
	 int j = 0;
	 for (uint32_t i = 0; i < nVertices; i++) {
		 colorStream << _colors[j++];
		 if (j >= _colors.size()) {
			 j = 0;
		 }
	 }

	 


}


  