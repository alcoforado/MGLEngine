# Contributing

## Scope

This document defines the expected workflow for contributing code to MGLEngine.

## Development Environment

Use the same baseline as project build requirements:

- Windows + MSVC (`cl.exe`)
- CMake + Ninja
- Vulkan SDK (`VULKAN_SDK` set)
- `vcpkg` in `PATH`

## Setup

```powershell
cmake --preset x64-debug
cmake --build --preset x64-debug
```

## Change Guidelines

Keep module boundaries clear:

- Put reusable interfaces/utilities in `MGLEngine.Shared`.
- Keep Vulkan-specific implementation details in `MGLEngine.Vulkan`.
- Keep app bootstrap/demo behavior in `MGLEngine.Core`.
- Prefer small, focused commits.
- Preserve existing public interfaces unless a breaking change is intentional and documented.
- Update docs (`README.md`, `ARCHITECTURE.md`, `CHANGELOG.md`) for behavior or structure changes.

## Code Style

- Use C++20.
- Follow existing naming/convention patterns in touched files.
- private class members starts with the prefix  _m
- Avoid broad refactors mixed with behavior changes in one commit.
- Add comments only for non-obvious logic.

## Testing

### API contracts and input validation

MGLEngine is a developer-facing library. Callers are expected to run Debug builds first to catch API misuse. Use `eassert` for runtime contract checks and `static_assert` for compile-time requirements, including valid bindings, compatible types, sizes, and layouts. Contract violations are programming errors; do not introduce recoverable validation results or exceptions for them. Keep required operations outside assertions so execution remains correct when assertions are disabled.

Applications and UI layers must validate end-user input before passing it to the engine. Runtime error handling remains appropriate for external failures, such as missing files or device errors.

`MGLEngine.Tests` contains Catch2-based tests, but the root CMake currently comments out test subdirectory inclusion.

To run tests, enable `add_subdirectory(MGLEngine.Tests)` in the root `CMakeLists.txt`, then rebuild and execute the test binary from the build folder.

When adding or changing logic:

- Add/adjust unit tests when practical.
- At minimum, verify affected executable/library builds successfully.

## Pull Request Checklist

- Code builds locally with `x64-debug` preset.
- New behavior is covered by tests or clearly validated manually.
- Relevant documentation updated.
- `CHANGELOG.md` updated under `Unreleased`.
