# Architecture

## Overview

MGLEngine is organized as a modular C++20 workspace with a shared abstraction layer and a Vulkan backend implementation.
For now Vulkan is the only implementation for the abstraction layer. Others will come out in the future.
At runtime, the primary flow is:

1. Application code requests an app builder through `MGLContainer`.
2. Builder collects window + app configuration.
3. Builder initializes `VulkanEngine` (implementation of `IMGLEngine`).
4. Engine sets up Vulkan resources and enters the render loop.

## Modules

## `MGLEngine.Shared`

Responsibilities:

- Core interfaces (`IAppBuilder`, `IMGLEngine`, `IShader`, `IDrawingObject`, etc.).
- Shared utility primitives (arrays, defragmented containers, observable, path/exception helpers, JSON parser).
- Shape service abstraction (`ShapesService`).
- Shared shader-related abstractions and generated shader headers.

Key role: contract layer between app-facing code and backend-specific engine implementation.

## `MGLEngine.Vulkan`

Responsibilities:

- Vulkan backend implementing shared interfaces.
- App builder implementation (`VulkanAppBuilder`).
- Engine implementation (`VulkanEngine`).
Vulkan context stack includes:

- instance
- physical/logical device
- surface/swapchain
- memory allocator (VMA)
- command pool/buffer, semaphores, fences

Key role: owns graphics API resources and render lifecycle.

## `MGLEngine.Core`

Responsibilities:

- Bootstrap executable.
- Configures window/app settings via `IAppBuilder`.
- Creates sample geometry (`OrthoRect2D`) and color shader draw object.
- Starts main render loop.

Key role: minimal executable demonstrating engine initialization and rendering.

## `MglEngine.HttpServer`

Responsibilities:

- Lightweight HTTP server wrapper over Boost.Asio/Beast.
- Middleware pipeline and route mapping.
- Route matching with parameterized path support.

Key role: network/API surface that can be used by app modules such as MCAD.

## `MGLEngine.MCAD`

Responsibilities:

- Wires HTTP routes to shape-related services/controllers.
- Intended integration app between HTTP API and rendering/domain services.

Current status: present in repository, but not included by default in root CMake.

## `MGLEngine.Tests`

Responsibilities:

- Catch2 tests for utility structures, parser behavior, HTTP routing/URL handling, and selected Vulkan context behavior.

Current status: present in repository, but not included by default in root CMake.

## Build-Time Flow

1. Root CMake validates toolchain (`vcpkg`, `git`, Vulkan SDK).
2. Required third-party libraries are found/installed via vcpkg.
3. Shared/Vulkan shader sources are compiled to generated header bytecode via `glslangValidator`.
4. Libraries are built, then `MGLEngine.Core` links against `MGLEngine.Shared` and `MGLEngine.Vulkan`.

## Key Abstractions

- `MGLContainer`: entry point to obtain the app builder.
- `IAppBuilder`: configuration + initialization surface.
- `IMGLEngine`: runtime engine contract (`Run`, shader registration, shape submission).
- `IShader` / `IDrawingObject`: rendering pipeline contracts shared across backends.

## Extension Points

- Add new rendering backends by implementing `IAppBuilder` + `IMGLEngine` contracts in a backend module.
- Add new draw object/shader families by extending shared shader/drawing interfaces and backend pipeline binding logic.
- Add new API endpoints through `MglEngine.HttpServer` route mappings and controllers.
