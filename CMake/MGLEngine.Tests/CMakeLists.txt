set(CMAKE_GENERATOR_PLATFORM "x64")
project(MGLEngine.Tests)




include_directories(${Vulkan_INCLUDE_DIRS}  "../")


include_directories(${Boost_INCLUDE_DIR})
message("Boost libraries found at ${Boost_LIBRARY_DIRS}")

# Create the executable
add_executable(${PROJECT_NAME}  "ArrayTest.cpp" "MGLEngine.Test.cpp" "MJsonTest.cpp" "ObservableTest.cpp" "ShapesTests.cpp" "stdafx.cpp" "stdafx.h" 
"targetver.h" "TemplateTests.cpp" "TestDefragArray.cpp" "Vulkan/SemaphorePoolTest.cpp" "Vulkan/VulkanContextTests.cpp" 
"Vulkan/VulkanTestsHelper.cpp" "Vulkan/VulkanTestsHelper.h" "HttpServerTest.cpp")

message ("GLF3 ${glfw3_DIR}")



message("Vulkan lib at ${LOCAL_EXTERNAL_LIBS}/vulkan-1.lib")

find_package("glfw3")

target_link_libraries	(${PROJECT_NAME} 
	                    MGLEngine.Shared
						MGLEngine.Vulkan
						MGLEngine.HttpServer
						${Vulkan_LIBRARIES}
						glfw)





						
