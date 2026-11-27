set(CMAKE_GENERATOR_PLATFORM "x64")
project(MGLEngine.Tests)

find_package(Catch2 3 CONFIG REQUIRED)





include_directories(${Boost_INCLUDE_DIR})
message("Boost libraries found at ${Boost_LIBRARY_DIRS}")
# Create the executable
add_executable(${PROJECT_NAME}  "main.cpp" "MeshUtilsTest.cpp" )

include(Catch)
catch_discover_tests(${PROJECT_NAME})






target_link_libraries	(${PROJECT_NAME} 
	                    MGLEngine.Shared
						Catch2::Catch2
						)





						
