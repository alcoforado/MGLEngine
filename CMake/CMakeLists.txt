set(CMAKE_SUPPRESS_REGENERATION true)
SET(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON CACHE INTERNAL "" FORCE)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>") 
#set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded") 
message("CMake Version ${CMAKE_VERSION}")
IF (WIN32)
    add_compile_definitions(_WIN32_WINNT=0x0A00 _DISABLE_CONSTEXPR_MUTEX_CONSTRUCTOR )


ENDIF()
    add_link_options("/VERBOSE:LIB")

set(VCPKG_VERBOSE ON)

if(POLICY CMP0167)  
  cmake_policy(SET CMP0167 NEW)
endif()

add_compile_options(-DBOOST_ENABLE_ASSERT_DEBUG_HANDLER)

find_program(VCPKG_EXECUTABLE vcpkg)
if (NOT VCPKG_EXECUTABLE)
    message(FATAL_ERROR "vcpkg not found please install vcpkg yourseLf and rerun the installer")
endif()


cmake_path(GET VCPKG_EXECUTABLE PARENT_PATH VCPKG_INSTALL_FOLDER)
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_INSTALL_FOLDER}/scripts/buildsystems/vcpkg.cmake")
message("TOOLCHAIN FILE ${CMAKE_TOOLCHAIN_FILE}")


find_package(Git)
if (NOT Git_FOUND)
    message(FATAL_ERROR "git not found please install git yourservel and rerun the installer")
endif()


#VULKAN CHECK
SET(VULKAN_SDK $ENV{VULKAN_SDK})
if (NOT DEFINED VULKAN_SDK)
    message(FATAL_ERROR "Vulkan SDK not found, please define the VULKAN_SDK variable")
endif()
find_package(Vulkan REQUIRED)







set(VCPKG_TARGET_TRIPLET "x64-windows-static")

 


macro(install_if_not_found PACKAGE_NAME VCPKG_NAME)
    find_package(${PACKAGE_NAME}  QUIET )
    set(found "${${PACKAGE_NAME}_FOUND}")
    if (NOT found)
        message("Package ${PACKAGE_NAME} not found, installing.....")
        execute_process(
            COMMAND vcpkg.exe install "${VCPKG_NAME}:${VCPKG_TARGET_TRIPLET}"
            WORKING_DIRECTORY "${VCPKG_INSTALL_FOLDER}"
            RESULT_VARIABLE VCPKG_INSTALL_RESULT
        )
        if (NOT VCPKG_INSTALL_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to install package ${VCPKG_NAME}:${VCPKG_TARGET_TRIPLET} with vcpkg")
        endif()
        find_package(${PACKAGE_NAME}  REQUIRED )
    else()
        message("Package ${PACKAGE_NAME} found")
    endif()
endmacro()

macro(install_component_if_not_found PACKAGE_NAME PACKAGE_COMPONENT VCPKG_NAME)
    find_package(${PACKAGE_NAME} COMPONENTS ${PACKAGE_COMPONENT}  QUIET CONFIG NO_MODULE)
    set(found "${${PACKAGE_NAME}_FOUND}")
    if (NOT found)
        message("Package ${PACKAGE_NAME} not found, installing.....")
        execute_process(
            COMMAND vcpkg.exe install "${VCPKG_NAME}:${VCPKG_TARGET_TRIPLET}"
            WORKING_DIRECTORY "${VCPKG_INSTALL_FOLDER}"
            RESULT_VARIABLE VCPKG_INSTALL_RESULT
        )
        if (NOT VCPKG_INSTALL_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to install package ${VCPKG_NAME}:${VCPKG_TARGET_TRIPLET} with vcpkg")
        endif()
        find_package(${PACKAGE_NAME} COMPONENTS ${PACKAGE_COMPONENT}  REQUIRED CONFIG NO_MODULE)
    else()
        message("Package ${PACKAGE_NAME} COMPONENT ${PACKAGE_COMPONENT} found")
    endif()
endmacro()









cmake_minimum_required (VERSION 3.10)
set(VERBOSE "1")
set(LOCAL_EXTERNAL_LIBS "${CMAKE_CURRENT_SOURCE_DIR}/../References/lib/x64")
set(CMAKE_FIND_DEBUG_MODE Off)
set(VCPKG_TRACE_FIND_PACKAGE OFF)
project(MGLEngine)


set(VCPKG_INCLUDE_DIR "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include")


macro(print_all_variables)
    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
endmacro()
#print_all_variables()


install_if_not_found("glm" "GLM")
install_if_not_found("VulkanMemoryAllocator" "vulkan-memory-allocator")
install_if_not_found("glfw3" "glfw3")
install_if_not_found("Catch2" "catch2")
install_if_not_found("boost_stacktrace_basic" "boost-stacktrace")
install_if_not_found("boost_beast" "boost-beast")



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




















