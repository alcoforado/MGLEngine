set(CMAKE_GENERATOR_PLATFORM "x64")
project(MGLEngine.HttpServer)

# Create the executable
add_library(MGLEngine.HttpServer STATIC "HttpServer.h" "HttpServer.cpp" "IMiddleware.h" "WebApiMiddletier.h" "WebApiMiddletier.cpp" "boost_deps.h" "Utils.h" "Router.h" "Router.cpp" "Url.h" "WebApiContext.h" "WebApiContext.cpp" "HttpContext.h" "HttpResponse.h" "HttpResponse.cpp" "IController.h")

target_link_libraries(${PROJECT_NAME})

target_include_directories(MGLEngine.HttpServer PUBLIC ${Boost_INCLUDE_DIR})
