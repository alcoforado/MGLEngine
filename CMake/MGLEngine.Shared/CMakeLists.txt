set(CMAKE_GENERATOR_PLATFORM "x64")
project(MGLEngine.Shared)


# Create the executable
add_library(${PROJECT_NAME} STATIC "IMGLContainer.h" "IMGLEngine.h" "DrawTree/DrawInfo.h" "DrawTree/DrawTree.h" "DrawTree/IRenderResource.h" "Interfaces/IPainter2D.h" 
"Interfaces/ISerializable.h" "Interfaces/IShaderDataWriter.h" "Interfaces/IShape3D.cpp" "Interfaces/IShape3D.h" "Interfaces/IShapeHandle.h" "Interfaces/ITopology2D.cpp" 
"Interfaces/ITopology2D.h" "Interfaces/ITopology3D.cpp" "Interfaces/ITopology3D.h" "Painters/CyclicColor.h" "Painters/VerticeColor2D.cpp" "Painters/VerticeColor2D.h" 
"RenderPipeline/ICompiler.cpp" "RenderPipeline/ICompiler.h" "Shaders/IShader2D.h" "ShapesService/ShapeScene.cpp" "ShapesService/ShapeScene.h" "ShapesService/ShapesService.cpp" 
"ShapesService/ShapesService.h" "Topologies/Triangle2D.cpp" "Topologies/Triangle2D.h" 
"Utils/collection_functions.h" "Utils/eassert.cpp" "Utils/eassert.h" "Utils/Exception.cpp" 
"Utils/Exception.h" "Utils/NTree.h" "Utils/Observable.h" "Utils/opointer.h" 
"Utils/Path.cpp" "Utils/Path.h" "Utils/PoolBuffer.h" "Utils/shared_global.h" 
"Utils/UniqueNameGenerator.h" "Utils/Arrays/ArrayFunctions.h" "Utils/Arrays/ArraySelect.cpp" "Utils/Arrays/ArraySelect.h" "Utils/Arrays/FlagBitVector.h" "Utils/Arrays/IArray.h" 
"Utils/Arrays/Indices.cpp" "Utils/Arrays/Indices.h" "Utils/DefragArray/ArrayRegion.h" "Utils/DefragArray/CopyPlanSequenceDetail.h" "Utils/DefragArray/CopyRegion.h" 
"Utils/DefragArray/DefragArray.h" "Utils/JsonParser/mjson.cpp" "Utils/JsonParser/mjson.h" "VerticeData/Color2D.h" "Window/ICanvas.h" "Window/IWindow.h" "Window/IWindowEventHandler.cpp" 
"Window/IWindowEventHandler.h")


include_directories("../../References/include" "../")

target_link_libraries	(${PROJECT_NAME} 
						optimized ${Boost_LIBRARY_DIRS}/boost_system-vc140-mt.lib
						debug ${Boost_LIBRARY_DIRS}/../debug/lib/boost_system-vc140-mt-gd.lib
						)

