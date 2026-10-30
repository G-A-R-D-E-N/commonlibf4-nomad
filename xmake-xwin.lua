-- Cross-compile commonlibf4 (Non-VR) for Windows x64 from Linux with
-- clang-cl + xwin's MSVC CRT/SDK. Wine is not used or required. Entry point
-- for CI on the self-hosted commonlib-nonvr runner:
-- `xmake f -F xmake-xwin.lua ...`.
--
-- This project *is* CommonLibF4 (lib/commonlib-shared upstream requires
-- spdlog with header_only=false), which hits the same cross-compile trap
-- already worked through for Prisma-Matrix/CombatMod's own CommonLibF4
-- dependency: xmake's package manager still runs a real CMake
-- configure+install for spdlog even with header_only=true (it only toggles
-- -DSPDLOG_HEADER_ONLY=ON; CMake's own compiler sanity check still runs),
-- and that CMake invocation fails cross-compiling under this toolchain --
-- confirmed via two different live CI failures depending on exactly which
-- CMake step ran first: "clang-cl: error: no such file or directory:
-- '/libpath:/opt/xwin/crt/lib/x86_64'" and "lld-link: error: unknown
-- /machine argument: x86_64". header_only=true alone does not avoid this.
--
-- The fix that actually works, matching this same toolchain's own
-- ixwebsocket precedent (a compiled package xmake's manager "cannot
-- cross-compile ... optional=true alone still ATTEMPTS the fetch"):
-- system=true stops xmake's package manager from touching spdlog at all, no
-- CMake invocation of any kind. The real headers and compiled spdlog.lib,
-- staged host-wide for the org's other xwin runners, are wired in manually
-- instead (SPDLOG_COMPILED_LIB keeps spdlog's own inline impl out of every
-- translation unit, so no in-tree spdlog build is needed at all).
includes("toolchains/xwin-clang-cl.lua")
set_toolchains("xwin-clang-cl")
set_runtimes("MD")

add_requireconfs("spdlog", {system = true, optional = true, override = true})

add_defines("_CRT_USE_BUILTIN_OFFSETOF")
add_defines("NOGDI", "NOMINMAX", "WIN32_LEAN_AND_MEAN")
add_defines("SPDLOG_COMPILED_LIB", "SPDLOG_USE_STD_FORMAT", "SPDLOG_WCHAR_TO_UTF8_SUPPORT")

-- Staged Windows packages, shared org-wide (same host, same org-scoped
-- runners) with Prisma-Matrix/CombatMod -- not staged per-repo.
local pkgroot = os.getenv("PRISMA_WIN_PACKAGES") or "/opt/prisma-toolchain/win-packages"

local function die(msg)
    print("error: " .. msg)
    return STAGED_WINDOWS_TOOLCHAIN_NOT_FOUND()
end

local function staged_dir(letter, name, kind)
    for _, dir in ipairs(os.dirs(path.join(pkgroot, letter, name, "*", "*", kind))) do
        return dir
    end
    die("staged " .. name .. " " .. kind .. " not found under " .. pkgroot ..
        " -- set PRISMA_WIN_PACKAGES")
end

add_includedirs(staged_dir("s", "spdlog", "include"))
add_linkdirs(staged_dir("s", "spdlog", "lib"))
add_links("spdlog")

includes("xmake.lua")
