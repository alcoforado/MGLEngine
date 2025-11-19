
project(MGLEngine.App)




# Create the executable
add_executable(${PROJECT_NAME})



include_directories("${Vulkan_INCLUDE_DIRS}")


include_directories(${Boost_INCLUDE_DIR})

message("Vulkan Libraries ${Vulkan_LIBRARIES} ${VULKAN_INCLUDE_DIRS}")

configure_file("settings.json" ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries	(${PROJECT_NAME} 
	                    ${Vulkan_LIBRARIES}
						glfw

						debug ${Boost_LIBRARY_DIRS}/../debug/lib/boost_system-vc140-mt-gd.lib)




