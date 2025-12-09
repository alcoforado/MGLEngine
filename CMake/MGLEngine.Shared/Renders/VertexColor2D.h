#include <MGLEngine.Shared/Interfaces/IMesh.h>
#include <MGLEngine.Shared/Shaders/Color2D/ShaderColor2D.h>
#include <glm/glm.hpp>
class VertexColor2D : public IDrawingObject {
private:
	IMesh& _mesh;
	std::vector<glm::vec4> _colors;

public:
	VertexColor2D(IMesh& mesh, const std::vector<glm::vec4>& colors)
		:_mesh(mesh), _colors(colors) {
	}
	virtual uint32_t NVertices() override {
		return _mesh.NVertices();
	}
	virtual uint32_t NIndices() override {
		return _mesh.NIndices();
	}

	virtual std::type_info ShaderType() override {
		return typeid(ShaderColor2D);
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
