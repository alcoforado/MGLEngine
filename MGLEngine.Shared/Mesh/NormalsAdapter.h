#pragma once
#include <MGLEngine.Shared/Interfaces/IMesh3D.h>
#include <MGLEngine.Shared/Utils/MeshUtils.h>
class NormalsAdapter : public IMesh3DWithNormals {
	
	MeshUtils::TopologyWithNormals topology;
	float angleThresholdToMergeNormalsInDeg;
public:
	NormalsAdapter(IMesh3D& originalMesh,float angleThresholdToMergeNormalsInDeg=15)
	{
		std::vector<glm::vec3> pos(originalMesh.NVertices());
		std::vector<unsigned> indices(originalMesh.NIndices());

		InterleavedMemoryStream posStream(pos);
		IndicesMemoryStream indicesStream(indices);
		originalMesh.RenderMesh(MemoryStreamFloat3DAdapter(posStream), indicesStream);


		topology = MeshUtils::ComputeNormals(pos, indices, angleThresholdToMergeNormalsInDeg);
	}

	virtual uint32_t NVertices() {
		return topology.pos.size();
	}


	virtual uint32_t NIndices() override { 
		return topology.indices.size(); 
	}


	void RenderMesh(MemoryStreamFloat3DAdapter positions, IndicesMemoryStream& indices, MemoryStreamFloat3DAdapter normals) override
	{
		positions << topology.pos;
		indices << topology.indices;
		normals << topology.normals;

	}

	virtual void Draw(IDrawContext& context)
	{
		context.DrawIndexed();
	}




};