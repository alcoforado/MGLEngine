#pragma once
#include "Utils/DrawTree/DrawTree.h"
#include "../Shaders/IRenderContext.h"
#include "../RenderPipeline/VulkanPipeline.h"
class IRenderContext;
template<class T>
class VulkanDrawTreeParser
{
	IRenderContext& _context;
	DrawTree<T> &_tree;
	VulkanPipeline& _pipeline;
	VulkanStagingBuffer* _pVerticesBuffer;
	std::vector<VulkanCommandBuffer*> _commands;
public:
	VulkanDrawTreeParser(IRenderContext& context, VulkanPipeline& pipeline,DrawTree<T>& tree)
		:_context(context),_pipeline(pipeline),	_tree(tree)
	{
		_pVerticesBuffer = nullptr;
		assert(pipeline.IsLoaded());
		_pVerticesBuffer = new VulkanStagingBuffer(_context.GetMemoryManager(), 100 * sizeof(T));
	}
	
	void clearCommandsBuffers()
	{
		for (auto cmd : _commands)
		{
			delete cmd;
		}

	}

	void CreateCommands()
	{
		NTreeNode<DrawInfo<T>>* root = _tree.GetRoot();
		IArray<T> vertices = _pVerticesBuffer->ToArray<T>();
		vertices.Resize(root->GetData().Current.SizeV);
		_tree.ComputeSize();
		std::vector<unsigned> indices1(100);
		IArray<unsigned> is1(indices.data(),root->GetData().Current.SizeI);
		std::vector<unsigned> indices2(100);
		IArray<unsigned> is2(indices.data(), root->GetData().Future.SizeI);

		
		
		if (!_tree.NeedRedraw())
			return;
		if (root->GetData().Future.SizeV>vertices.capacity())
		{
			VulkanStagingBuffer *newBuff = new VulkanStagingBuffer(_context.GetMemoryManager(), root->GetData().Future.SizeV);
			IArray<T> newVertices = newBuff->ToArray<T>(root->GetData().Future.SizeV);
			

			_tree.UpdateVerticeData(newVertices)
		}st

		clearCommandsBuffers();
		auto framebuffers = _pipeline.GetVulkanSwapChainFramebuffers();
		glm::vec4 color(0, 0, 0, 1.0);
		for (int i = 0; i<framebuffers->Size(); i++)
		{
			auto framebuffer = framebuffers->GetFramebuffer(i);
			VulkanCommandBuffer* comm = new VulkanCommandBuffer(_context.GetCommandPool());
			comm->BeginRenderPass(framebuffer, glm::vec4(0, 0, 0, 0));
			comm->BindPipeline(&_pipeline);
			
			//Allocate vertex buffer
			
			
			if ()
			
			comm->BindVertexBuffer(*_buffer);
			comm->Draw(GetVertices().size(), 1, 0, 0);
			comm->EndRenderPass();
			comm->End();
			_commands.push_back(comm);
		}


		
	}


	~VulkanDrawTreeParser()
	{}




};

