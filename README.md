# MGLEngine

MGLEngine is a C++20 graphics engine workspace centered on a Vulkan renderer, with shared engine abstractions, a demo core app, and optional HTTP/MCAD modules.

## Repository Layout

- `MGLEngine.Shared`: Common interfaces, utility containers, shape services, and shader-related shared code.
- `MGLEngine.Vulkan`: Vulkan-specific engine implementation, context/device/swapchain pipeline, and window integration.
- `MGLEngine.Core`: Main executable that initializes the engine and renders a sample colored rectangle.
- `MglEngine.HttpServer`: Ignore this project for now
- `MGLEngine.MCAD`: Ignore this project for now.
- `MGLEngine.Tests`: Catch2 test suite for containers, JSON parser, router/URL behavior, and Vulkan context pieces.

## Prerequisites

- Windows (project is configured for Win32/Visual C++ toolchain).
- Visual Studio C++ Build Tools (or equivalent `cl.exe` environment).
- CMake (preset file provided).
- Ninja.
- Git.
- `vcpkg` installed and available in `PATH` as `vcpkg.exe`.
- Vulkan SDK installed with `VULKAN_SDK` environment variable set.

## Build

From repository root:

```powershell
cmake --preset x64-debug
cmake --build --preset x64-debug
```

Build output is generated under:

- `out/build/x64-debug`

## Run

Core demo app:

```powershell
.\out\build\x64-debug\MGLEngine.Core\MGLEngine.Core.exe
```

Behavior today:

- Creates an 800x800 window.
- Enables Vulkan debug layer and VSync.
- Initializes Vulkan 1.2 app configuration.
- Draws a sample 2D orthographic rectangle with color shader.

## Dependency Management

Top-level CMake attempts to locate and install required packages through `vcpkg` when missing:

- `glm`
- `vulkan-memory-allocator`
- `glfw3`
- `catch2`
- `boost-stacktrace`
- `boost-beast`

## Notes About Current CMake Topology

In the current root `CMakeLists.txt`, only these subprojects are enabled by default:

- `MGLEngine.Shared`
- `MGLEngine.Vulkan`
- `MGLEngine.Core`

`MGLEngine.HttpServer`, `MGLEngine.Tests`, and `MGLEngine.MCAD` are present but currently commented out at root level. Enable their `add_subdirectory(...)` lines to include them in configure/build.

## Shaders

- `MGLEngine.Shared` compiles `.vert`/`.frag` shader files into header bytecode through `glslangValidator.exe` from the Vulkan SDK.
- Shader header generation runs as part of CMake build rules.

## Troubleshooting

- `vcpkg not found`: ensure `vcpkg.exe` is in `PATH`.
- `Vulkan SDK not found`: set `VULKAN_SDK` environment variable to SDK install path.
- Missing `cl.exe`: open a Visual Studio Developer PowerShell/Prompt before running CMake.
