
project(MGLEngine.Core)

file(GLOB_RECURSE HEADERS "${PROJECT_SOURCE_DIR}/*.h")
file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/*.cpp")


# Create the executable
add_executable(${PROJECT_NAME}  ${SOURCES} )


# Copy specific configuration files
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
       "${CMAKE_CURRENT_SOURCE_DIR}/assets"
       "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
)

include_directories("${Vulkan_INCLUDE_DIRS}" "../")



message("Vulkan Libraries ${Vulkan_LIBRARIES} ${VULKAN_INCLUDE_DIRS}")


#target_include_directories(MGLEngine.Core PUBLIC ${Boost_INCLUDE_DIR})

target_link_libraries	(${PROJECT_NAME} 
						MGLEngine.Shared
						MGLEngine.Vulkan
						Vulkan::Vulkan
						glfw)




