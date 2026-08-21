# CommonLibF4 Unified

This is the active local CommonLibF4 workspace for OG and AE plugin development.

It is based on the OGAE2 CommonLibF4 line and keeps its 3-slot relocation layout.

## Supported Runtimes

- OG: Fallout 4 `1.10.163`
- NG: slot preserved from OGAE2, not an active support target
- AE: Fallout 4 `1.11.221`

VR is not supported in this workspace.

AE builds require the Address Library package for Fallout 4 `1.11.221`.

## Build Requirements

- XMake `3.0.0+`
- C++23 compiler, MSVC or Clang-CL

## Build

```powershell
xmake f -y
xmake build
```

The default build produces:

```text
build/windows/x64/release/commonlibf4.lib
build/windows/x64/release/commonlib-shared.lib
```

## Visual Studio Project Generation

```powershell
xmake project -k vsxmake
```

## CMake Consumers

Existing CMake plugin projects can consume the xmake-built Unified library through:

```powershell
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCommonLibF4Unified_DIR=D:/CommonLibF4-Unified/cmake
cmake --build build --config Release
```

Plugin CMake files should link the package target:

```cmake
find_package(CommonLibF4Unified REQUIRED CONFIG)
target_link_libraries(MyPlugin PRIVATE CommonLibF4Unified::CommonLibF4)
```

The helper below generates the `F4SEPlugin_Version` export required by AE F4SE:

```cmake
commonlibf4_unified_add_plugin_version(
	MyPlugin
	NAME MyPlugin
	VERSION ${PROJECT_VERSION}
	COMPATIBLE_RUNTIMES OG AE
)
```

## Relocation ID Policy

Runtime ID slots are:

```cpp
{ OG, NG, AE }
```

NG values are preserved as inherited from OGAE2. Current development and runtime testing target OG and AE only.

The `commonlib-shared` submodule is currently upstream `commonlib-shared` plus the Unified `REL::VariantID` offset resolution change. No additional `commonlib-shared` changes were needed for the `1.11.221` update.
