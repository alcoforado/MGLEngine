#include <MGLEngine.Shared/common.h>
#include <MGLEngine.Shared/Shaders/Color2D/ShaderColor2D.h>
#include <MGLEngine.Shared/Interfaces/IMGLEngine.h>

#include <glm/glm.hpp>
#include <typeinfo>
class VertexColor2D : public IDrawingObject {
private:
	IMesh2D& _mesh;
	std::vector<glm::vec4> _colors;

public:
	VertexColor2D(IMGLEngine &engine,IMesh2D& mesh, const std::vector<glm::vec4>& colors)
		:_mesh(mesh), _colors(colors) {
		engine.AddShape<ShaderColor2D>(*this);
	}
	virtual uint32_t NVertices() override {
		return _mesh.NVertices();
	}
	virtual uint32_t NIndices() override {
		return _mesh.NIndices();
	}

	

	virtual void RenderData(IRenderSerializationContext& context) override
	{
		auto& posStream = context.GetVerticeAttribute("position2d");
		auto& indexStream = context.GetIndicesStream();
		_mesh.RenderMesh(context.GetVerticeAttribute("position2d"),context.GetIndicesStream());


		auto& colorStream = context.GetVerticeAttribute("color");
		auto nVertices = _mesh.NVertices();
		//Fill colors in a round-robin fashion
		int j = 0;
		for (uint32_t i = 0; i < nVertices;i++) {
			colorStream << _colors[j++];
			if (j >= _colors.size()) {
				j = 0;
			}
		}
	}
	
	virtual void Draw(IDrawContext& context) override
	{
		_mesh.Draw(context);
	}
	virtual ~VertexColor2D() {}

};
