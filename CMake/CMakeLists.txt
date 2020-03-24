set(CMAKE_SUPPRESS_REGENERATION true)
set(VCPKG_INSTALL_FOLDER "${CMAKE_CURRENT_BINARY_DIR}/vcpkg")
set(CMAKE_GENERATOR_PLATFORM "x64")

find_package(Git)
if (NOT Git_FOUND)
    message("git not found please install git yourservel and rerun the installer")
endif()
SET(CMAKE_CXX_STANDARD 14)

if (NOT EXISTS "${VCPKG_INSTALL_FOLDER}/README.md")
    message("======= Downloading vcpkg =======")
    execute_process(COMMAND ${GIT_EXECUTABLE} clone https://github.com/Microsoft/vcpkg.git
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                    RESULT_VARIABLE GIT_SUBMOD_RESULT)
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

project(MGLEngine)

message("CMake BuildList: ${CMAKE_CURRENT_LIST_DIR} ")

add_subdirectory(MGLEngine.HttpServer)





message("Toolchain set to ${CMAKE_TOOLCHAIN_FILE}")


