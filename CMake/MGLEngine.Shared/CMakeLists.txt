set(CMAKE_GENERATOR_PLATFORM "x64")
project(MGLEngine.Shared)




message("====== Looking for Vulkan Shader compiler  =====")
set(SHADER_COMPILER_EXEC "$ENV{VULKAN_SDK}/Bin/glslangValidator.exe")
if (EXISTS ${SHADER_COMPILER_EXEC})
	message("===== Vulkan Compiler  found at ${SHADER_COMPILER_EXEC}")
else()
	message("====== Error, Vulkan SDK not found =====")
endif()

message("====== Compiling Shaders to Headers =====")
file(GLOB_RECURSE SHADERS "${PROJECT_SOURCE_DIR}/*.frag" "${PROJECT_SOURCE_DIR}/*.vert")



foreach (sh IN LISTS SHADERS )
	
	string(REPLACE ".vert" "_vert.h" HEADER_FILE ${sh})
    if(HEADER_FILE STREQUAL sh)
	    string(REPLACE ".frag" "_frag.h" HEADER_FILE ${sh})
    endif()
    cmake_path(GET HEADER_FILE FILENAME VAR_NAME)  #VAR_NAME=filename with extension
    string(REPLACE ".h" "" VAR_NAME ${VAR_NAME}) #Remove .h extension
    message("\t\tProcessing Shader File: ${sh} to Header: ${HEADER_FILE} Into Variable ${VAR_NAME}")
	add_custom_command(
	OUTPUT "${HEADER_FILE}" 
	COMMAND ${SHADER_COMPILER_EXEC} ARGS -V --vn ${VAR_NAME} -o ${HEADER_FILE}  ${sh}
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	DEPENDS "${sh}" 
    VERBATIM
	)
	list(APPEND SHADERS_HEADERS "${HEADER_FILE}")
endforeach()

message ("Shader Header lists is : ${SHADERS_HEADERS}")

# Create the executable
add_library(${PROJECT_NAME} STATIC
    ${SHADERS_HEADERS}
    "Interfaces/IAppConfiguration.h"
    "Interfaces/IDrawingObject.h"
    "Interfaces/IMesh.h"
    "Interfaces/IShader.h"
    "Interfaces/IShaderConfiguration.h"
    "Interfaces/IShapeHandle.h"
    "Interfaces/IMGLEngine.h"
    "Interfaces/IAppBuilder.h"

    "Interfaces/IWindowOptions.h"
    "MGLContainer.h"
    "Shaders/Color2D/ShaderColor2D.cpp"
    "Shaders/Color2D/ShaderColor2D.h"
    "Shaders/IShader2D.h"
    
    
    "ShapesService/ShapesService.cpp"
    "ShapesService/ShapesService.h"
    "Utils/Arrays/ArrayFunctions.h"
    "Utils/Arrays/ArraySelect.cpp"
    "Utils/Arrays/ArraySelect.h"
    "Utils/Arrays/FlagBitVector.h"
    "Utils/Arrays/IArray.h"
    "Utils/Arrays/Indices.cpp"
    "Utils/Arrays/Indices.h"
    "Utils/Arrays/IndicesMemoryStream.cpp"
    "Utils/Arrays/IndicesMemoryStream.h"
    "Utils/Arrays/InterleavedMemoryStream.cpp"
    "Utils/Arrays/InterleavedMemoryStream.h"
    "Utils/CommitTag.cpp"
    "Utils/CommitTag.h"
    "Utils/DefragArray/ArrayRegion.h"
    "Utils/DefragArray/CopyPlanSequenceDetail.h"
    "Utils/DefragArray/CopyRegion.h"
    "Utils/DefragArray/DefragArray.h"
    "Utils/Exception.cpp"
    "Utils/Exception.h"
    "Utils/NTree.h"
    "Utils/Observable.h"
    "Utils/Path.cpp"
    "Utils/Path.h"
    "Utils/PoolBuffer.h"
    "Utils/UniqueNameGenerator.h"
    "Utils/collection_functions.h"
    "Utils/eassert.cpp"
    "Utils/eassert.h"
    "Utils/opointer.h"
    "Utils/shared_global.h"
    "Utils/JsonParser/mjson.cpp"
    "Utils/JsonParser/mjson.h"
    "Window/IWindow.h"
    "Window/IWindowEventHandler.cpp"
    "Window/IWindowEventHandler.h"
 "Interfaces/IRenderDataContext.h" 
 "Interfaces/IDrawContext.h" 
 "Mesh/OrthoRect2D.h" 
 "Shaders/Color2D/VertexColor2D.h" 
 "Interfaces/IMGLEngine.h" 
 "Shaders/FieldType.h"
 "Shaders/BindingManager.h" "Shaders/BindingManager.cpp")
target_include_directories(MGLEngine.Shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)
