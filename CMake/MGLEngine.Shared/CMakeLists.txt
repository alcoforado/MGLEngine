set(CMAKE_GENERATOR_PLATFORM "x64")
project(MGLEngine.Shared)



# Create the executable
add_library(${PROJECT_NAME} STATIC  "MGLContainer.h"     "Interfaces/IPainter2D.h" 
"Interfaces/ISerializable.h" "Interfaces/IShaderDataWriter.h" "Interfaces/IShape3D.cpp" "Interfaces/IShape3D.h" "Interfaces/IShapeHandle.h" "Interfaces/ITopology2D.cpp" 
"Interfaces/ITopology2D.h" "Interfaces/ITopology3D.cpp" "Interfaces/ITopology3D.h"    
"RenderPipeline/ICompiler.cpp" "RenderPipeline/ICompiler.h" "Shaders/IShader2D.h" "ShapesService/ShapeScene.cpp" "ShapesService/ShapeScene.h" "ShapesService/ShapesService.cpp" 
"ShapesService/ShapesService.h" "Mesh/Triangle2D.cpp" "Mesh/Triangle2D.h" 
"Utils/collection_functions.h" "Utils/eassert.cpp" "Utils/eassert.h" "Utils/Exception.cpp" 
"Utils/Exception.h" "Utils/NTree.h" "Utils/Observable.h" "Utils/opointer.h" 
"Utils/Path.cpp" "Utils/Path.h" "Utils/PoolBuffer.h" "Utils/shared_global.h" 
"Utils/UniqueNameGenerator.h" "Utils/Arrays/ArrayFunctions.h" "Utils/Arrays/ArraySelect.cpp" "Utils/Arrays/ArraySelect.h" "Utils/Arrays/FlagBitVector.h" "Utils/Arrays/IArray.h" 
"Utils/Arrays/Indices.cpp" "Utils/Arrays/Indices.h" "Utils/DefragArray/ArrayRegion.h" "Utils/DefragArray/CopyPlanSequenceDetail.h" "Utils/DefragArray/CopyRegion.h" 
"Utils/DefragArray/DefragArray.h" "Utils/JsonParser/mjson.cpp" "Utils/JsonParser/mjson.h"   "Window/IWindow.h" "Window/IWindowEventHandler.cpp" 
"Window/IWindowEventHandler.h" "Utils/CommitTag.h" "Utils/CommitTag.cpp"  "Interfaces/IShader.h" "Interfaces/IShaderConfiguration.h" "Interfaces/IMesh.h" "Interfaces/IDrawingObject.h" "Utils/Arrays/InterleavedMemoryStream.h" "Utils/Arrays/InterleavedMemoryStream.cpp" "Utils/Arrays/IndicesMemoryStream.h" "Utils/Arrays/IndicesMemoryStream.cpp" "Interfaces/IAppConfiguration.h" "Interfaces/IVulkanApp.h" "Interfaces/IWindowOptions.h" "Shaders/Color2D/ShaderColor2D.h" "Shaders/Color2D/ShaderColor2D.cpp")


message("====== Compiling Shaders to Headers =====")
file(GLOB_RECURSE SHADERS "${PROJECT_SOURCE_DIR}/*.frag" "${PROJECT_SOURCE_DIR}/SPIR-V/*.vert")


foreach (sh IN LISTS SHADERS )
	string(REPLACE ".vert" "_vert" VAR_NAME ${sh})
	string(REPLACE ".frag" "_frag" VAR_NAME ${VAR_NAME})
	string(REPLACE "/SPIR-V/" "/SPIR-V/headers/" HEADER_FILE ${VAR_NAME})
	string(REPLACE "${PROJECT_SOURCE_DIR}/SPIR-V/" "" VAR_NAME ${VAR_NAME})
	message("\t\tProcessing Shader File: ${sh} to Header: ${HEADER_FILE}.h Into Variable ${VAR_NAME}")
	add_custom_command(
	OUTPUT "${HEADER_FILE}.h" 
	COMMAND ${SHADER_COMPILER_EXEC} ARGS -V --vn ${VAR_NAME} -o "${HEADER_FILE}.h"  ${sh}
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	DEPENDS "${sh}" 
	)
	list(APPEND SHADERS_HEADERS "${HEADER_FILE}.h")
endforeach()



target_include_directories(MGLEngine.Shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)


