set(CMAKE_GENERATOR_PLATFORM "x64")
project(MGLEngine.Vulkan)

#list the shader files
set (SHADERS  "SPIR-V/canvas2D.vert" "SPIR-V/canvas2D.frag")
list (TRANSFORM SHADERS  REPLACE "[.]" "_" OUTPUT_VARIABLE SHADER_HEADERS_1 )
list (TRANSFORM SHADER_HEADERS_1  APPEND  ".h" OUTPUT_VARIABLE SHADER_HEADERS )


# Create the executable
add_library( ${PROJECT_NAME} ${SHADERS} ${SHADER_HEADERS}
"MGLContainerVulkan.cpp" "MGLContainerVulkan.h" "MGLEngineVulkan.cpp" "MGLEngineVulkan.h" "VulkanMemoryProperties.cpp" "VulkanMemoryProperties.h" 
"VulkanUtils.cpp" "VulkanUtils.h" "MemoryManager/IMappedMemory.h" "MemoryManager/VulkanBuffer.h" "MemoryManager/VulkanGPUBuffer.h" 
"MemoryManager/VulkanMappedAutoSyncBuffer.h" "MemoryManager/VulkanMappedBuffer.h" "MemoryManager/VulkanMemoryManager.cpp" 
"MemoryManager/VulkanMemoryManager.h" "RenderPipeline/Compiler.cpp" "RenderPipeline/Compiler.h" "RenderPipeline/FragmentShaderByteCode.cpp" 
"RenderPipeline/FragmentShaderByteCode.h" "RenderPipeline/VertexShaderByteCode.cpp" "RenderPipeline/VertexShaderByteCode.h" 
"RenderPipeline/VulkanCommandBuffer.cpp" "RenderPipeline/VulkanCommandBuffer.h" "RenderPipeline/VulkanCommandPool.cpp" "RenderPipeline/VulkanCommandPool.h" 
"RenderPipeline/VulkanCommands.cpp" "RenderPipeline/VulkanCommands.h" "RenderPipeline/VulkanDrawTreeParser.h" "RenderPipeline/VulkanFence.cpp" 
"RenderPipeline/VulkanFence.h" "RenderPipeline/VulkanFramebuffer.cpp" "RenderPipeline/VulkanFramebuffer.h" "RenderPipeline/VulkanInputLayout.cpp" 
"RenderPipeline/VulkanInputLayout.h" "RenderPipeline/VulkanPipeline.cpp" "RenderPipeline/VulkanPipeline.h" "RenderPipeline/VulkanRenderPass.cpp" 
"RenderPipeline/VulkanRenderPass.h" "RenderPipeline/VulkanSemaphore.cpp" "RenderPipeline/VulkanSemaphore.h" "RenderPipeline/VulkanSemaphorePool.cpp" 
"RenderPipeline/VulkanSemaphorePool.h" "RenderPipeline/VulkanSubPass.cpp" "RenderPipeline/VulkanSubPass.h" "RenderPipeline/VulkanSwapChainFramebuffers.cpp" 
"RenderPipeline/VulkanSwapChainFramebuffers.h" "RenderResources/IVulkanRenderSlot.h" "RenderResources/IVulkanSlotBinding.cpp" 
"RenderResources/IVulkanSlotBinding.h" "RenderResources/SlotManager.cpp" "RenderResources/SlotManager.h" "RenderResources/UniformBufferSlot.h" 
"RenderResources/VulkanDescriptorSet.cpp" "RenderResources/VulkanDescriptorSet.h" "RenderResources/VulkanDescriptorSetLayout.cpp" 
"RenderResources/VulkanDescriptorSetLayout.h" "RenderResources/VulkanDescriptorSetPool.cpp" "RenderResources/VulkanDescriptorSetPool.h" 
"RenderResources/VulkanResourceLoadContext.h" "Shaders/IVulkanRenderContext.cpp" "Shaders/IVulkanRenderContext.h" "Shaders/IVulkanShader.h" 
"Shaders/ShaderColor2D.cpp" "Shaders/ShaderColor2D.h" "SPIR-V/shaders_bytecode.h" "VulkanContext/IDrawContext.h" 
"VulkanContext/VulkanCommandBatchCollection.cpp" "VulkanContext/VulkanCommandBatchCollection.h" "VulkanContext/VulkanContext.cpp" 
"VulkanContext/VulkanContext.h" "VulkanContext/VulkanInstance.cpp" "VulkanContext/VulkanInstance.h" "VulkanContext/VulkanLayerProperties.cpp" 
"VulkanContext/VulkanLayerProperties.h" "VulkanContext/VulkanLogicalDevice.cpp" "VulkanContext/VulkanLogicalDevice.h" "VulkanContext/VulkanPhysicalDevice.cpp" 
"VulkanContext/VulkanPhysicalDevice.h" "VulkanContext/VulkanQueue.cpp" "VulkanContext/VulkanQueue.h" "VulkanContext/VulkanSurface.cpp" 
"VulkanContext/VulkanSurface.h" "VulkanContext/VulkanSwapChain.cpp" "VulkanContext/VulkanSwapChain.h" "Window/MWindow.cpp" "Window/MWindow.h" 
"Window/VulkanCanvas.cpp" "Window/VulkanCanvas.h"  )

include_directories("../../References/include" "../")

message("====== Looking for Vulkan Shader compiler  =====")
set(SHADER_COMPILER_EXEC "$ENV{VULKAN_SDK}/Bin/glslangValidator.exe")
if (EXISTS ${SHADER_COMPILER_EXEC})
	message("===== Vulkan Compiler  found at ${SHADER_COMPILER_EXEC}")
else()
	message("====== Error, Vulkan SDK not found =====")
endif()




foreach (sh IN LISTS SHADERS )
	string(REPLACE "." "_" HEADER_NAME ${sh})
	string(REGEX MATCH "[^/]+$" VAR_NAME ${HEADER_NAME})
	add_custom_command(
	OUTPUT "${HEADER_NAME}.h" 
	COMMAND ${SHADER_COMPILER_EXEC} ARGS -V --vn ${VAR_NAME} -o "${HEADER_NAME}.h"  ${sh}
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	)
	list(APPEND SHADERS_HEADERS "${HEADER_NAME}")
endforeach()

	add_custom_command(
	OUTPUT "SPIR-V/shaders_bytecode"
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	)






target_link_libraries	(${PROJECT_NAME})

