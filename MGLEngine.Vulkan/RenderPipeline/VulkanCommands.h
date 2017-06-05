#pragma once

enum VulkanCommandsFlags {BIND_PIPELINE};
class IVulkanCommands
{
public:
	virtual VulkanCommandsFlags	GetCommandType() = 0;
	virtual void Execute() = 0;
	virtual ~IVulkanCommands(){}
};


class VulkanCommandBindPipeline : public IVulkanCommands
{
	virtual VulkanCommandsFlags	GetCommandType() override {
		return  BIND_PIPELINE;
	};
	virtual void Execute() override {
	}
	virtual ~VulkanCommandBindPipeline() override {}

};
