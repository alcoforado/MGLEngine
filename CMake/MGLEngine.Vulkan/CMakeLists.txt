set(CMAKE_GENERATOR_PLATFORM "x64")
project(MGLEngine.Vulkan)




include_directories( "../" "${Vulkan_INCLUDE_DIRS}")

message("====== Looking for Vulkan Shader compiler  =====")
set(SHADER_COMPILER_EXEC "$ENV{VULKAN_SDK}/Bin/glslangValidator.exe")
if (EXISTS ${SHADER_COMPILER_EXEC})
	message("===== Vulkan Compiler  found at ${SHADER_COMPILER_EXEC}")
else()
	message("====== Error, Vulkan SDK not found =====")
endif()




message("====== Compiling Shaders to Headers =====")
file(GLOB_RECURSE SHADERS "${PROJECT_SOURCE_DIR}/SPIR-V/*.frag" "${PROJECT_SOURCE_DIR}/SPIR-V/*.vert")


foreach (sh IN LISTS SHADERS )
	string(REPLACE ".vert" "_vert" VAR_NAME ${sh})
	string(REPLACE ".frag" "_frag" VAR_NAME ${VAR_NAME})
	string(REPLACE "/SPIR-V/" "/SPIR-V/headers/" HEADER_FILE ${VAR_NAME})
	string(REPLACE "${PROJECT_SOURCE_DIR}/SPIR-V/" "" VAR_NAME ${VAR_NAME})
	message("\t\tProcessing Shader File: ${sh} to Header: ${HEADER_FILE}.h Into Variable ${VAR_NAME}")
	add_custom_command(
	OUTPUT "${HEADER_FILE}.h" 
	COMMAND ${SHADER_COMPILER_EXEC} ARGS -V --vn ${VAR_NAME} -o "${HEADER_FILE}.h"  ${sh}
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	DEPENDS "${sh}" 
	)
	list(APPEND SHADERS_HEADERS "${HEADER_FILE}.h")
endforeach()

add_custom_target(CompileShaderHeaders ALL DEPENDS ${SHADERS_HEADERS})
	



# Create the executable
add_library( ${PROJECT_NAME} ${SHADERS} ${SHADER_HEADERS} "VulkanApp.cpp"
    "VulkanContext/VulkanMemoryProperties.cpp" "VulkanContext/VulkanMemoryProperties.h"  "Window/MWindow.cpp"
"VulkanUtils.cpp" "VulkanUtils.h" "MemoryManager/IMappedMemory.h" "MemoryManager/VulkanBuffer.h" "MemoryManager/VulkanGPUBuffer.h" 
"MemoryManager/VulkanMappedAutoSyncBuffer.h" "MemoryManager/VulkanMappedBuffer.h" "MemoryManager/VulkanMemoryManager.cpp" 
"MemoryManager/VulkanMemoryManager.h" "RenderPipeline/Compiler.cpp" "RenderPipeline/Compiler.h" "RenderPipeline/FragmentShaderByteCode.cpp" 
"RenderPipeline/FragmentShaderByteCode.h" "RenderPipeline/VertexShaderByteCode.cpp" "RenderPipeline/VertexShaderByteCode.h" 
"RenderPipeline/VulkanCommandBuffer.cpp" "RenderPipeline/VulkanCommandBuffer.h" "RenderPipeline/VulkanCommandPool.cpp" "RenderPipeline/VulkanCommandPool.h" 
"RenderPipeline/VulkanCommands.cpp" "RenderPipeline/VulkanCommands.h" "DrawTree/VulkanDrawTreeParser.h" "RenderPipeline/VulkanFence.cpp" 
"RenderPipeline/VulkanFence.h" "RenderPipeline/VulkanFramebuffer.cpp" "RenderPipeline/VulkanFramebuffer.h" "RenderPipeline/VulkanInputLayout.cpp" 
"RenderPipeline/VulkanInputLayout.h" "RenderPipeline/VulkanPipeline.cpp" "RenderPipeline/VulkanPipeline.h" "RenderPipeline/VulkanRenderPass.cpp" 
"RenderPipeline/VulkanRenderPass.h" "RenderPipeline/VulkanSemaphore.cpp" "RenderPipeline/VulkanSemaphore.h" "RenderPipeline/VulkanSemaphorePool.cpp" 
"RenderPipeline/VulkanSemaphorePool.h" "RenderPipeline/VulkanSubPass.cpp" "RenderPipeline/VulkanSubPass.h" "RenderPipeline/VulkanSwapChainFramebuffers.cpp" 
"RenderPipeline/VulkanSwapChainFramebuffers.h" "RenderResources/IVulkanRenderSlot.h" "RenderResources/IVulkanSlotBinding.cpp" 
"RenderResources/IVulkanSlotBinding.h" "RenderResources/SlotManager.cpp" "RenderResources/SlotManager.h" "RenderResources/UniformBufferSlot.h" 
"RenderResources/VulkanDescriptorSet.cpp" "RenderResources/VulkanDescriptorSet.h" "RenderResources/VulkanDescriptorSetLayout.cpp" 
"RenderResources/VulkanDescriptorSetLayout.h" "RenderResources/VulkanDescriptorSetPool.cpp" "RenderResources/VulkanDescriptorSetPool.h" 
 "Shaders/IVulkanRenderContext.cpp" "Shaders/IVulkanRenderContext.h" "Shaders/IVulkanShader.h" 
"Shaders/ShaderColor2D.cpp" "Shaders/ShaderColor2D.h" "SPIR-V/shaders_bytecode.h" "VulkanContext/IDrawContext.h" 
"VulkanContext/VulkanCommandBatchCollection.cpp" "VulkanContext/VulkanCommandBatchCollection.h" "VulkanContext/VulkanContext.cpp" 
"VulkanContext/VulkanContext.h" "VulkanContext/VulkanInstance.cpp" "VulkanContext/VulkanInstance.h" "VulkanContext/VulkanLayerProperties.cpp" 
"VulkanContext/VulkanLayerProperties.h" "VulkanContext/VulkanLogicalDevice.cpp" "VulkanContext/VulkanLogicalDevice.h" "VulkanContext/VulkanPhysicalDevice.cpp" 
"VulkanContext/VulkanPhysicalDevice.h" "VulkanContext/VulkanQueue.cpp" "VulkanContext/VulkanQueue.h" "VulkanContext/VulkanSurface.cpp" 
"VulkanContext/VulkanSurface.h" "VulkanContext/VulkanSwapChain.cpp" "VulkanContext/VulkanSwapChain.h"   
    "DrawTree/VulkanResourceLoader.h" "DrawTree/VulkanResourceLoader.cpp" "DrawTree/IVulkanResourceLoader.h" "DrawTree/TreeExecutionContext.h"
 "DrawTree/VulkanInternalData.h" "VulkanApp.cpp" "VulkanApp.h" "VulkanContext/VulkanConfiguration.h")



target_link_libraries	(${PROJECT_NAME})

