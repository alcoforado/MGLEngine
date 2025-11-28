set(CMAKE_SUPPRESS_REGENERATION true)
SET(CMAKE_CXX_STANDARD 20)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>") 
IF (WIN32)
    add_compile_definitions(_WIN32_WINNT=0x0A00 )
ENDIF()

if(POLICY CMP0167)  
  cmake_policy(SET CMP0167 NEW)
endif()

add_compile_options(-DBOOST_ENABLE_ASSERT_DEBUG_HANDLER)

if (NOT DEFINED VCPKG_INSTALL_FOLDER)
    set(VCPKG_INSTALL_FOLDER "${CMAKE_SOURCE_DIR}/../vcpkg")
endif()

find_package(Git)
if (NOT Git_FOUND)
    message("git not found please install git yourservel and rerun the installer")
endif()



SET(VULKAN_SDK $ENV{VULKAN_SDK})
if (NOT DEFINED VULKAN_SDK)
    message(FATAL_ERROR "Vulkan SDK not found, please define the VULKAN_SDK variable")
endif()



if (NOT EXISTS "${VCPKG_INSTALL_FOLDER}/README.md")
    message("======= Downloading vcpkg =======")
    execute_process(COMMAND ${GIT_EXECUTABLE} clone https://github.com/Microsoft/vcpkg.git
                    WORKING_DIRECTORY "${VCPKG_INSTALL_FOLDER}/../"
                    RESULT_VARIABLE GIT_SUBMOD_RESULT)
else()
    message("VCPKG found at ${VCPKG_INSTALL_FOLDER}")
endif()


if (NOT EXISTS "${VCPKG_INSTALL_FOLDER}/vcpkg.exe")
    message("======= compiling vcpkg =======")
    exec_program("bootstrap-vcpkg.bat" ${VCPKG_INSTALL_FOLDER})
    message("${VC_PACKAGE_RESULT}")
    message("${VC_PACKAGE_ERROR}")
endif()

set(CMAKE_TOOLCHAIN_FILE "${VCPKG_INSTALL_FOLDER}/scripts/buildsystems/vcpkg.cmake")

set(VCPKG_TARGET_TRIPLET "x64-windows-static")

 

macro(install_if_not_found PACKAGE_NAME VCPKG_NAME)
    find_package(${PACKAGE_NAME}   QUIET)
    set(found "${${PACKAGE_NAME}_FOUND}")
    if (NOT found)
        message("Package ${PACKAGE_NAME} not found, installing.....")
        exec_program("vcpkg.exe" ${VCPKG_INSTALL_FOLDER} ARGS install "${VCPKG_NAME}:${VCPKG_TARGET_TRIPLET}")
        find_package(${PACKAGE_NAME}  REQUIRED)
    else()
        message("Package ${PACKAGE_NAME} found")
    endif()
endmacro()








cmake_minimum_required (VERSION 3.10)
set(VERBOSE "1")
set(LOCAL_EXTERNAL_LIBS "${CMAKE_CURRENT_SOURCE_DIR}/../References/lib/x64")
project(MGLEngine)


set(VCPKG_INCLUDE_DIR "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include")

install_if_not_found("boost_beast" "boost-beast")
install_if_not_found("boost_stacktrace_basic" "boost-stacktrace")
install_if_not_found("glm" "GLM")
install_if_not_found("glfw3" "glfw3")
install_if_not_found("Catch2" "catch2")



find_package(Vulkan REQUIRED)

include_directories("${VCPKG_INCLUDE_DIR}")




#message("Configuring MGLEngine.HttpServer")
#add_subdirectory(MGLEngine.HttpServer)
message("Configuring MGLEngine.Shared")
add_subdirectory(MGLEngine.Shared)
message("Configuring MGLEngine.Vulkan")
add_subdirectory(MGLEngine.Vulkan)
#message("Configuring MGLEngine.Tests")
#add_subdirectory(MGLEngine.Tests)
#message("Configuring MGLEngine.MCADs")
#add_subdirectory(MGLEngine.MCAD)
message("Configuring MGLEngine.Core")
add_subdirectory(MGLEngine.Core)



macro(print_all_variables)
    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
endmacro()


print_all_variables()















