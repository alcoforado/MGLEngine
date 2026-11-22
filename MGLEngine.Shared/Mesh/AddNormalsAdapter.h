#pragma once
#include <MGLEngine.Shared/Interfaces/IMesh3D.h>
class Mesh3DNormalsAdapter : IMesh3DWithNormals {
	IMesh3D& mesh;
public:
	Mesh3DNormalsAdapter(IMesh3D& originalMesh)
		:mesh(originalMesh)
	{

	}

	virtual uint32_t NVertices() {
		return 0;
	}


	virtual uint32_t NIndices() override { return 0; }

	void RenderMesh(MemoryStreamFloat3DAdapter positions, IndicesMemoryStream& indices, MemoryStreamFloat3DAdapter& normals) override
	{


	}




};