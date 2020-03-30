set(CMAKE_GENERATOR_PLATFORM "x64")
project(MGLEngine.MCAD)


# Create the executable
add_executable(${PROJECT_NAME}  "main.cpp")


include_directories("../../References/include" "../")

message("======= Requiring Boost =======")
find_package("Boost" REQUIRED)
include_directories(${Boost_INCLUDE_DIR})


target_link_libraries	(${PROJECT_NAME} 
						optimized ${Boost_LIBRARY_DIRS}/boost_system-vc140-mt.lib
						debug ${Boost_LIBRARY_DIRS}/../debug/lib/boost_system-vc140-mt-gd.lib
						)


