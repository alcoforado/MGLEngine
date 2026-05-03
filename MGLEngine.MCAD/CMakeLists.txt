
project(MGLEngine.MCAD)




# Create the executable
add_executable(${PROJECT_NAME}  "main.cpp"  "ShapesController.h" "ShapesController.cpp" "settings.json")



include_directories("${Vulkan_INCLUDE_DIRS}"  "../")


include_directories(${Boost_INCLUDE_DIR})

message("Vulkan Libraries ${Vulkan_LIBRARIES} ${VULKAN_INCLUDE_DIRS}")

configure_file("settings.json" ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries	(${PROJECT_NAME} 
	                    MGLEngine.HttpServer
	                    MGLEngine.Shared
						MGLEngine.Vulkan
						${Vulkan_LIBRARIES}
						glfw)




