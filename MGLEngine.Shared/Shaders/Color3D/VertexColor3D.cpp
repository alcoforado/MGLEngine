#pragma once
#include "VertexColor3D.h"
#include "color3D_vert.h"
#include "color3D_frag.h"
#include <MGLEngine.Shared/Shaders/GlobalBindings.h>
class ShaderColor3D :IShader {
public:
	//ShaderConfiguration
	virtual void Init(ShaderConfiguration& config)
	{
		config.EnableCulling(true);
		config.DeclareVertexAttribute_FloatVec3("position3d", 0);
		config.DeclareVertexAttribute_FloatVec4("color", 1);
		config.SetVerticeShader(color3D_vert, sizeof(color3D_vert));
		config.SetFragmentShader(color3D_frag, sizeof(color3D_frag));
		glm::mat4 m(1);
		config.DeclareUbo(UboBindingCollection::CameraTransform, Std140Mat4(m));


		

	}

};




VertexColor3D::VertexColor3D(MGLEngine& engine, IMesh3D& mesh, const std::vector<glm::vec4>& colors)
	:_mesh(mesh), _colors(colors) {
	engine.AddShape<ShaderColor3D>(*this);
}


void VertexColor3D::RenderData(RenderSerializationContext& context)
{

	auto& posStream = context.GetVerticeAttribute("position3d");
	auto& indexStream = context.GetIndicesStream();
	_mesh.RenderMesh(context.GetVerticeAttribute("position3d"), context.GetIndicesStream());


	auto& colorStream = context.GetVerticeAttribute("color");
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