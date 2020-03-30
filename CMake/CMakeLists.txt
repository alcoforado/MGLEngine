set(CMAKE_SUPPRESS_REGENERATION true)

if (NOT DEFINED VCPKG_INSTALL_FOLDER)
    set(VCPKG_INSTALL_FOLDER "${CMAKE_SOURCE_DIR}/../vcpkg")
endif()

find_package(Git)
if (NOT Git_FOUND)
    message("git not found please install git yourservel and rerun the installer")
endif()
SET(CMAKE_CXX_STANDARD 14)

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



cmake_minimum_required (VERSION 3.5)
set(VERBOSE "1")
set(LOCAL_EXTERNAL_LIBS "${CMAKE_CURRENT_SOURCE_DIR}/../References/lib/x64")
project(MGLEngine)

message("CMake BuildList: ${CMAKE_CURRENT_LIST_DIR} ")
message("Toolchain set to ${CMAKE_TOOLCHAIN_FILE}")

add_subdirectory(MGLEngine.HttpServer)
add_subdirectory(MGLEngine.Shared)
add_subdirectory(MGLEngine.Vulkan)
add_subdirectory(MGLEngine.Tests)
add_subdirectory(MGLEngine.MCAD)






















