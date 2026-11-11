#include <MGLEngine.Shared/common.h>
#include <MGLEngine.Shared/MGLEngine.h>

#include <glm/glm.hpp>
#include <typeinfo>
class VertexColor3D : public IDrawingObject {
private:
	IMesh3D& _mesh;
	std::vector<glm::vec4> _colors;

public:
	VertexColor3D(MGLEngine& engine, IMesh3D& mesh, const std::vector<glm::vec4>& colors);
	
	virtual uint32_t NVertices() override {
		return _mesh.NVertices();
	}
	virtual uint32_t NIndices() override {
		return _mesh.NIndices();
	}



	virtual void RenderData(RenderSerializationContext& context) override;
	

	virtual void Draw(IDrawContext& context) override
	{
		_mesh.Draw(context);
	}
	virtual ~VertexColor3D() {}

};
