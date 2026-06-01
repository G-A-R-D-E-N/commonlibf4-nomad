# CommonLibF4 Unified

CommonLibF4 workspace for OG and AE plugin development.

## Supported Runtimes

- OG: Fallout 4 `1.10.163`
- NG: not an active support target
- AE: Fallout 4 `1.11.221`

## Build Requirements

- XMake `3.0.0+`
- C++23 compiler, MSVC or Clang-CL

## Installation

Clone this repository with its Unified `commonlib-shared` submodule:

```powershell
git clone --recurse-submodules https://github.com/EnclaveShrew/commonlibf4-unified.git
cd commonlibf4-unified
```

If the repository was cloned without submodules, initialize them before building:

```powershell
git submodule sync --recursive
git submodule update --init --recursive
```

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
