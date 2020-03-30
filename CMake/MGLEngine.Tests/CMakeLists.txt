set(CMAKE_GENERATOR_PLATFORM "x64")
project(MGLEngine.Tests)




include_directories("../../References/include" "../")

message("======= Requiring Boost =======")
find_package("Boost" REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
message("Boost libraries found at ${Boost_LIBRARY_DIRS}")

# Create the executable
add_executable(${PROJECT_NAME}  "ArrayTest.cpp" "MGLEngine.Test.cpp" "MJsonTest.cpp" "ObservableTest.cpp" "ShapesTests.cpp" "stdafx.cpp" "stdafx.h" 
"targetver.h" "TemplateTests.cpp" "TestDefragArray.cpp" "Vulkan/SemaphorePoolTest.cpp" "Vulkan/VulkanContextTests.cpp" 
"Vulkan/VulkanTestsHelper.cpp" "Vulkan/VulkanTestsHelper.h")

message("Vulkan lib at ${LOCAL_EXTERNAL_LIBS}/vulkan-1.lib")
target_link_libraries	(${PROJECT_NAME} 
	                    MGLEngine.Shared
						MGLEngine.Vulkan
						${LOCAL_EXTERNAL_LIBS}/vulkan-1.lib
						${LOCAL_EXTERNAL_LIBS}/glfw3.lib
						debug ${Boost_LIBRARY_DIRS}/../debug/lib/boost_system-vc140-mt-gd.lib)





						
