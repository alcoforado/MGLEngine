cmake_minimum_required (VERSION 3.5)
set(CMAKE_SUPPRESS_REGENERATION true)
project(MGLEngine)
add_subdirectory(MGLEngine.HttpServer)
set(VERBOSE "1")

find_package(Git)
if (NOT Git_FOUND)
    message("git not found please install git yourservel and rerun the installer")
endif()

set(VCPKG_INSTALL_FOLDER "${CMAKE_CURRENT_BINARY_DIR}/vcpkg")
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

message("Toolchain set to ${CMAKE_TOOLCHAIN_FILE}")

message("======= Installing boost-beast =======")
exec_program("vcpkg.exe" ${VCPKG_INSTALL_FOLDER} ARGS install boost-beast:x64-windows)
