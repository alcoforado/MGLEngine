set(CMAKE_GENERATOR_PLATFORM "x64")
project(MGLEngine.Tests)





include_directories(${Boost_INCLUDE_DIR})
message("Boost libraries found at ${Boost_LIBRARY_DIRS}")
# Create the executable
add_executable(${PROJECT_NAME}  "main.cpp" "MeshUtils.cpp" )






target_link_libraries	(${PROJECT_NAME} 
	                    MGLEngine.Shared
						Catch2::Catch2
						)





						
