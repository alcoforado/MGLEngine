set(CMAKE_GENERATOR_PLATFORM "x64")
project(MGLEngine.MCAD)


# Create the executable
add_executable(${PROJECT_NAME}  "main.cpp" )


include_directories("../../References/include" "../")

message("======= Requiring Boost =======")
find_package("Boost" REQUIRED)
include_directories(${Boost_INCLUDE_DIR})




target_link_libraries	(${PROJECT_NAME} 
	                    MGLEngine.HttpServer
	                    MGLEngine.Shared
						MGLEngine.Vulkan
						${LOCAL_EXTERNAL_LIBS}/vulkan-1.lib
						${LOCAL_EXTERNAL_LIBS}/glfw3.lib
						debug ${Boost_LIBRARY_DIRS}/../debug/lib/boost_system-vc140-mt-gd.lib)




