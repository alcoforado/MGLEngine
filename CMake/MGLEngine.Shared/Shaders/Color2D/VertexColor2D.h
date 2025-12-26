#include <MGLEngine.Shared/Interfaces/IMesh.h>
#include <MGLEngine.Shared/Shaders/Color2D/ShaderColor2D.h>
#include <MGLEngine.Shared/Interfaces/IMGLEngine.h>

#include <glm/glm.hpp>
#include <typeinfo>
class VertexColor2D : public IDrawingObject {
private:
	IMesh& _mesh;
	std::vector<glm::vec4> _colors;

public:
	VertexColor2D(IMGLEngine &engine,IMesh& mesh, const std::vector<glm::vec4>& colors)
		:_mesh(mesh), _colors(colors) {
		engine.AddShape<ShaderColor2D>(*this);
	}
	virtual uint32_t NVertices() override {
		return _mesh.NVertices();
	}
	virtual uint32_t NIndices() override {
		return _mesh.NIndices();
	}

	

	virtual void RenderData(IRenderDataContext& context) override
	{
		_mesh.RenderData(context);
		auto& colorStream = context.GetVerticeAttribute("color");
		auto nVertices = _mesh.NVertices();
		//Fill colors in a round-robin fashion
		int j = 0;
		for (int i = 0; i < nVertices;i++) {
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
