set(CMAKE_GENERATOR_PLATFORM "x64")
project(MGLEngine.HttpServer)

message("======= Installing boost-beast =======")
exec_program("vcpkg.exe" ${VCPKG_INSTALL_FOLDER} ARGS install boost-beast)

find_package("Boost" REQUIRED)
include_directories(${Boost_INCLUDE_DIR})



# Create the executable
add_executable(MGLEngine.HttpServer main.cpp)

target_link_libraries	(${PROJECT_NAME} 
						optimized ${Boost_LIBRARY_DIRS}/boost_system-vc140-mt.lib
						debug ${Boost_LIBRARY_DIRS}/../debug/lib/boost_system-vc140-mt-gd.lib
						)