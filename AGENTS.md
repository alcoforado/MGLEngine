# Repository guidance

## Scope

This is a Windows-oriented C++20 graphics engine built with CMake, MSVC, Ninja, and Vulkan. Work primarily in `MGLEngine.Shared`, `MGLEngine.Vulkan`, and `MGLEngine.Core`.

Ignore `MglEngine.HttpServer` and `MGLEngine.MCAD` unless the user explicitly includes them in a task. Do not enable or modify those projects as part of routine engine work.

<!-- CODEGRAPH_START -->
## CodeGraph

When a `.codegraph/` directory exists at the repository root, use CodeGraph before searching or reading code to understand or locate an implementation:

- Prefer the `codegraph_explore` MCP tool. Query exact symbols or repository-relative file paths to obtain current source, callers, and dependencies. Use fully qualified paths to avoid similarly named files in excluded projects.
- Shell fallback: `codegraph explore "<symbols or question>"`.
- Use direct reads for configuration and documentation, or specific source that CodeGraph omits or flags as stale.
- If there is no index, use normal search tools. Do not initialize an index unless requested.
<!-- CODEGRAPH_END -->

## Code map

- `MGLEngine.Core/main.cpp` is the demo entry point. It configures `AppBuilder`, initializes `MGLEngine`, registers drawing objects, and calls `Run()`. The currently selected example renders a textured sprite; the file also contains a colored rectangle example.
- `MGLEngine.Shared` contains the public engine API, interfaces, mesh serialization, shader definitions, resource loading, and utility containers. It is a static library with an explicit CMake source list.
- `MGLEngine.Shared/MGLEngine.h` implements templated `AddShape<ShaderType>`. Shader types initialize `ShaderConfiguration` and are registered by `std::type_index`.
- `MGLEngine.Shared/Shaders/ShaderContext.cpp` groups drawing objects by shader, calculates buffer sizes and offsets, and serializes vertex and index data. `GlobalBindingsTable` collects shader bindings and image assignments.
- `MGLEngine.Shared/Interfaces/IGraphicLibrary.h` defines the backend interface. Shared currently depends directly on Vulkan through `MGLEngine.cpp` and `AppBuilder.cpp`; do not assume the libraries are fully decoupled.
- `MGLEngine.Vulkan/VulkanEngineContainer.cpp` creates `MGL::VulkanGL`. `VulkanGL` coordinates pipelines, texture loading, descriptors, buffers, command recording, synchronization, swapchain recreation, and the render loop.
- `MGLEngine.Vulkan/VulkanContext` contains Vulkan resource wrappers; `VulkanApp` contains pipeline and resource support; `Window/MWindow.cpp` provides window integration.
- `MGLEngine.Tests` contains Catch2 tests, but is disabled in the root CMake configuration and includes older engine APIs.

## Configure, build, and run

Use a Visual Studio developer shell with the x64 compiler environment, Ninja, Git, and `vcpkg.exe` on `PATH`. Install the Vulkan SDK and set `VULKAN_SDK`. The project uses the `x64-windows-static` vcpkg triplet and the static MSVC runtime (debug variant for Debug).

From the repository root:

```powershell
cmake --preset x64-debug
cmake --build out/build/x64-debug --target MGLEngine.Core
```

Only a configure preset is defined. Do not use `cmake --build --preset x64-debug` unless a matching build preset has been added.

Run the demo from its output directory because it configures the image root as `./assets`:

```powershell
Push-Location out/build/x64-debug/MGLEngine.Core
try { .\MGLEngine.Core.exe } finally { Pop-Location }
```

Core copies its `assets` directory beside the executable after building. The current demo requests `texture.jpg`, uses an 800-by-800 window, enables validation and VSync, and requests Vulkan 1.2. Running it requires a working Vulkan device, windowing environment, and validation layer.

Root CMake enables Shared, Vulkan, and Core. Configuration can invoke vcpkg to install missing dependencies, including GLM, Vulkan Memory Allocator, stb, gli, GLFW, Catch2, and Boost packages. Configuration is therefore not necessarily a read-only or offline operation.

The declared CMake minimum is 3.10, but the project uses newer features such as `cmake_path` and preset version 3. Use CMake 3.21 or newer; do not infer actual compatibility from the minimum declaration. Windows-specific compiler, linker, and shader compiler settings mean cross-platform support must be verified rather than assumed.

## Editing conventions and invariants

- Follow nearby C++ formatting and naming: PascalCase types and methods, underscore-prefixed private members, and repository-root include paths such as `<MGLEngine.Shared/...>`. Avoid unrelated formatting changes or spelling renames in existing APIs such as `VerticeDataLayout`.
- Keep drawing and shader abstractions in Shared and Vulkan operations in the backend where practical. Inspect existing dependencies before moving code across library boundaries.
- Drawing objects registered with `AddShape` are retained through raw pointers; their meshes may also be held by reference. Keep both alive for all serialization and drawing, as the demo does by calling `Run()` within the objects' scope.
- Keep `NVertices()` and `NIndices()` consistent with the data emitted by `RenderData`/`RenderMesh`. Preserve stride, alignment, attribute offsets, buffer capacity, and per-object index/vertex offsets across serialization and command recording.
- Shader attribute names and locations, GLSL inputs, sampler names and bindings, registration configuration, and Vulkan descriptor layouts must agree. Check both Shared shader configuration and backend handling when changing any of them.
- Vulkan resource changes must preserve creation/destruction order, GPU synchronization, image layouts, and swapchain recreation behavior. Inspect ownership before changing pointers or cleanup paths; existing code mixes raw pointers and shared-pointer helpers.
- Edit GLSL `.vert` and `.frag` sources rather than manually changing generated bytecode arrays. CMake invokes `$env:VULKAN_SDK/Bin/glslangValidator.exe` to generate headers in the source tree. Review resulting diffs for relevant generated changes.
- Add new compiled Shared/Vulkan source files to their explicit CMake lists. Core uses recursive source globbing. Reconfigure after adding files or shaders: globbing does not use `CONFIGURE_DEPENDS`, and root CMake suppresses regeneration.
- Treat bundled third-party code such as `Utils/JsonParser/json.hpp` as vendor code; prefer changes to project wrappers rather than broad edits to it.

## Validation

- For engine changes, configure as needed and build the affected target plus `MGLEngine.Core` to catch integration and linking issues.
- For shader or rendering changes, rebuild generated shader headers and, when a graphical Vulkan environment is available, run the demo and check validation output and visible behavior. State when visual validation was unavailable.
- Do not claim tests ran merely because a build succeeded. Root CMake currently comments out `add_subdirectory(MGLEngine.Tests)`, and the test CMake file does not register tests with CTest.
- The existing test executable includes HTTP tests and links the excluded HTTP target. Vulkan tests also reference older paths/types and include an interactive rendering case. Simply enabling the tests is not a reliable validation workflow. If a task needs tests, establish a focused, buildable setup for the affected engine code without pulling excluded projects into scope.
- Report the commands actually run and any dependency, environment, or existing build failures separately from the change being made.
