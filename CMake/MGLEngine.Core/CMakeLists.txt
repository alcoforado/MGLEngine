
project(MGLEngine.Core)

file(GLOB_RECURSE HEADERS "${PROJECT_SOURCE_DIR}/*.h")
file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/*.cpp")


# Create the executable
add_executable(${PROJECT_NAME} "VulkanApp.ixx" ${SOURCES} )



include_directories("${Vulkan_INCLUDE_DIRS}")



message("Vulkan Libraries ${Vulkan_LIBRARIES} ${VULKAN_INCLUDE_DIRS}")

configure_file("settings.json" ${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(MGLEngine.Core PUBLIC ${Boost_INCLUDE_DIR})

target_link_libraries	(${PROJECT_NAME} 
						MGLEngine.Shared
						MGLEngine.Vulkan
	                    ${Vulkan_LIBRARIES}
						glfw)




