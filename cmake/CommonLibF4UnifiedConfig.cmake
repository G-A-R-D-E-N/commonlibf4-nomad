include_guard(GLOBAL)

get_filename_component(_CommonLibF4Unified_DEFAULT_ROOT "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)

set(
	CommonLibF4Unified_ROOT
	"${_CommonLibF4Unified_DEFAULT_ROOT}"
	CACHE PATH
	"Path to the CommonLibF4 Unified root"
)

set(
	CommonLibF4Unified_LIBRARY_CONFIG
	"release"
	CACHE STRING
	"CommonLibF4 Unified xmake library configuration"
)

set(
	CommonLibF4Unified_LIBRARY
	"${CommonLibF4Unified_ROOT}/build/windows/x64/${CommonLibF4Unified_LIBRARY_CONFIG}/commonlibf4.lib"
	CACHE FILEPATH
	"Path to the CommonLibF4 Unified static library"
)

set(
	CommonLibF4Unified_SHARED_LIBRARY
	"${CommonLibF4Unified_ROOT}/build/windows/x64/${CommonLibF4Unified_LIBRARY_CONFIG}/commonlib-shared.lib"
	CACHE FILEPATH
	"Path to the CommonLibF4 Unified commonlib-shared static library"
)

set(
	CommonLibF4Unified_XMAKE_PACKAGE_CACHE
	"${CommonLibF4Unified_ROOT}/.xmake/windows/x64/cache/package"
	CACHE FILEPATH
	"Path to the CommonLibF4 Unified xmake package cache"
)

set(
	CommonLibF4Unified_SPDLOG_ROOT
	""
	CACHE PATH
	"Path to the spdlog package used by CommonLibF4 Unified"
)

if (NOT EXISTS "${CommonLibF4Unified_LIBRARY}")
	message(
		FATAL_ERROR
		"CommonLibF4 Unified library was not found: ${CommonLibF4Unified_LIBRARY}. Run xmake -y in ${CommonLibF4Unified_ROOT} first."
	)
endif ()

if (NOT EXISTS "${CommonLibF4Unified_SHARED_LIBRARY}")
	message(
		FATAL_ERROR
		"CommonLibF4 Unified commonlib-shared library was not found: ${CommonLibF4Unified_SHARED_LIBRARY}. Run xmake f -y and xmake build in ${CommonLibF4Unified_ROOT} first."
	)
endif ()

if (NOT CommonLibF4Unified_SPDLOG_ROOT)
	if (NOT EXISTS "${CommonLibF4Unified_XMAKE_PACKAGE_CACHE}")
		message(
			FATAL_ERROR
			"CommonLibF4 Unified xmake package cache was not found: ${CommonLibF4Unified_XMAKE_PACKAGE_CACHE}. Run xmake f -y in ${CommonLibF4Unified_ROOT} first."
		)
	endif ()

	file(READ "${CommonLibF4Unified_XMAKE_PACKAGE_CACHE}" _CommonLibF4Unified_PACKAGE_CACHE)
	string(REPLACE "\r\n" "\n" _CommonLibF4Unified_PACKAGE_CACHE "${_CommonLibF4Unified_PACKAGE_CACHE}")
	string(REPLACE "\r" "\n" _CommonLibF4Unified_PACKAGE_CACHE "${_CommonLibF4Unified_PACKAGE_CACHE}")
	string(REGEX MATCHALL "[^\n]+" _CommonLibF4Unified_PACKAGE_LINES "${_CommonLibF4Unified_PACKAGE_CACHE}")

	set(_CommonLibF4Unified_IN_SPDLOG FALSE)
	foreach (_CommonLibF4Unified_LINE IN LISTS _CommonLibF4Unified_PACKAGE_LINES)
		if (_CommonLibF4Unified_LINE MATCHES "^[ \t]*spdlog[ \t]*=")
			set(_CommonLibF4Unified_IN_SPDLOG TRUE)
		endif ()

		if (_CommonLibF4Unified_IN_SPDLOG AND _CommonLibF4Unified_LINE MATCHES "^[ \t]*installdir[ \t]*=[ \t]*\\[\\[(.*)\\]\\]")
			set(CommonLibF4Unified_SPDLOG_ROOT "${CMAKE_MATCH_1}" CACHE PATH "Path to the spdlog package used by CommonLibF4 Unified" FORCE)
			break()
		endif ()
	endforeach ()
endif ()

if (NOT CommonLibF4Unified_SPDLOG_ROOT)
	message(FATAL_ERROR "Could not resolve the spdlog package used by CommonLibF4 Unified.")
endif ()

file(TO_CMAKE_PATH "${CommonLibF4Unified_SPDLOG_ROOT}" _CommonLibF4Unified_SPDLOG_ROOT)
set(CommonLibF4Unified_SPDLOG_ROOT "${_CommonLibF4Unified_SPDLOG_ROOT}" CACHE PATH "Path to the spdlog package used by CommonLibF4 Unified" FORCE)
set(CommonLibF4Unified_SPDLOG_LIBRARY "${CommonLibF4Unified_SPDLOG_ROOT}/lib/spdlog.lib")

if (NOT EXISTS "${CommonLibF4Unified_SPDLOG_LIBRARY}")
	message(FATAL_ERROR "CommonLibF4 Unified spdlog library was not found: ${CommonLibF4Unified_SPDLOG_LIBRARY}")
endif ()

if (NOT EXISTS "${CommonLibF4Unified_SPDLOG_ROOT}/include/spdlog/spdlog.h")
	message(FATAL_ERROR "CommonLibF4 Unified spdlog headers were not found: ${CommonLibF4Unified_SPDLOG_ROOT}/include")
endif ()

if (NOT TARGET CommonLibF4Unified::spdlog)
	add_library(CommonLibF4Unified::spdlog STATIC IMPORTED GLOBAL)
	set_target_properties(
		CommonLibF4Unified::spdlog
		PROPERTIES
			IMPORTED_LOCATION "${CommonLibF4Unified_SPDLOG_LIBRARY}"
			INTERFACE_COMPILE_DEFINITIONS "SPDLOG_COMPILED_LIB;SPDLOG_USE_STD_FORMAT;SPDLOG_WCHAR_TO_UTF8_SUPPORT"
			INTERFACE_INCLUDE_DIRECTORIES "${CommonLibF4Unified_SPDLOG_ROOT}/include"
	)
endif ()

if (NOT TARGET CommonLibF4Unified::CommonLibShared)
	add_library(CommonLibF4Unified::CommonLibShared STATIC IMPORTED GLOBAL)
	set_target_properties(
		CommonLibF4Unified::CommonLibShared
		PROPERTIES
			IMPORTED_LOCATION "${CommonLibF4Unified_SHARED_LIBRARY}"
			INTERFACE_COMPILE_DEFINITIONS "COMMONLIB_RUNTIMECOUNT=3"
			INTERFACE_COMPILE_FEATURES cxx_std_23
			INTERFACE_INCLUDE_DIRECTORIES "${CommonLibF4Unified_ROOT}/lib/commonlib-shared/include"
			INTERFACE_LINK_LIBRARIES "CommonLibF4Unified::spdlog"
	)
endif ()

if (NOT TARGET CommonLibF4Unified::CommonLibF4)
	add_library(CommonLibF4Unified::CommonLibF4 STATIC IMPORTED GLOBAL)
	set_target_properties(
		CommonLibF4Unified::CommonLibF4
		PROPERTIES
			IMPORTED_LOCATION "${CommonLibF4Unified_LIBRARY}"
			INTERFACE_COMPILE_DEFINITIONS "COMMONLIB_RUNTIMECOUNT=3;WINVER=0x0601;_WIN32_WINNT=0x0601"
			INTERFACE_COMPILE_FEATURES cxx_std_23
			INTERFACE_INCLUDE_DIRECTORIES "${CommonLibF4Unified_ROOT}/lib/commonlib-shared/include;${CommonLibF4Unified_ROOT}/include"
			INTERFACE_LINK_LIBRARIES "CommonLibF4Unified::CommonLibShared;CommonLibF4Unified::spdlog;Version.lib;Advapi32.lib;Bcrypt.lib;D3D11.lib;D3DCompiler.lib;Dbghelp.lib;Dxgi.lib;Ole32.lib;Shell32.lib;User32.lib;Ws2_32.lib"
	)
endif ()

if (NOT TARGET CommonLibF4::CommonLibF4)
	add_library(CommonLibF4::CommonLibF4 INTERFACE IMPORTED GLOBAL)
	set_target_properties(
		CommonLibF4::CommonLibF4
		PROPERTIES
			INTERFACE_LINK_LIBRARIES CommonLibF4Unified::CommonLibF4
	)
endif ()

function(commonlibf4_unified_add_plugin_version TARGET_NAME)
	set(_options)
	set(_oneValueArgs NAME AUTHOR VERSION)
	set(_multiValueArgs COMPATIBLE_RUNTIMES)
	cmake_parse_arguments(_CLF4_PLUGIN "${_options}" "${_oneValueArgs}" "${_multiValueArgs}" ${ARGN})

	if (NOT TARGET "${TARGET_NAME}")
		message(FATAL_ERROR "commonlibf4_unified_add_plugin_version target does not exist: ${TARGET_NAME}")
	endif ()

	if (NOT _CLF4_PLUGIN_NAME)
		set(_CLF4_PLUGIN_NAME "${TARGET_NAME}")
	endif ()

	if (NOT DEFINED _CLF4_PLUGIN_AUTHOR)
		set(_CLF4_PLUGIN_AUTHOR "")
	endif ()

	if (NOT _CLF4_PLUGIN_VERSION)
		set(_CLF4_PLUGIN_VERSION "${PROJECT_VERSION}")
	endif ()

	string(REPLACE "." ";" _CLF4_PLUGIN_VERSION_PARTS "${_CLF4_PLUGIN_VERSION}")
	list(LENGTH _CLF4_PLUGIN_VERSION_PARTS _CLF4_PLUGIN_VERSION_PART_COUNT)

	set(_CLF4_PLUGIN_VERSION_MAJOR 0)
	set(_CLF4_PLUGIN_VERSION_MINOR 0)
	set(_CLF4_PLUGIN_VERSION_PATCH 0)

	if (_CLF4_PLUGIN_VERSION_PART_COUNT GREATER 0)
		list(GET _CLF4_PLUGIN_VERSION_PARTS 0 _CLF4_PLUGIN_VERSION_MAJOR)
	endif ()

	if (_CLF4_PLUGIN_VERSION_PART_COUNT GREATER 1)
		list(GET _CLF4_PLUGIN_VERSION_PARTS 1 _CLF4_PLUGIN_VERSION_MINOR)
	endif ()

	if (_CLF4_PLUGIN_VERSION_PART_COUNT GREATER 2)
		list(GET _CLF4_PLUGIN_VERSION_PARTS 2 _CLF4_PLUGIN_VERSION_PATCH)
	endif ()

	if (NOT _CLF4_PLUGIN_COMPATIBLE_RUNTIMES)
		set(_CLF4_PLUGIN_COMPATIBLE_RUNTIMES OG AE)
	endif ()

	set(_CLF4_PLUGIN_COMPATIBLE_EXPRESSIONS)
	foreach (_CLF4_PLUGIN_RUNTIME IN LISTS _CLF4_PLUGIN_COMPATIBLE_RUNTIMES)
		string(TOUPPER "${_CLF4_PLUGIN_RUNTIME}" _CLF4_PLUGIN_RUNTIME_UPPER)

		if (_CLF4_PLUGIN_RUNTIME_UPPER STREQUAL "OG" OR _CLF4_PLUGIN_RUNTIME_UPPER STREQUAL "F4")
			list(APPEND _CLF4_PLUGIN_COMPATIBLE_EXPRESSIONS "F4SE::RUNTIME_1_10_163")
		elseif (_CLF4_PLUGIN_RUNTIME_UPPER STREQUAL "AE")
			list(APPEND _CLF4_PLUGIN_COMPATIBLE_EXPRESSIONS "F4SE::RUNTIME_1_11_191")
		else ()
			message(FATAL_ERROR "Unsupported CommonLibF4 Unified runtime in plugin metadata: ${_CLF4_PLUGIN_RUNTIME}")
		endif ()
	endforeach ()

	string(JOIN ", " _CLF4_PLUGIN_COMPATIBLE_CODE ${_CLF4_PLUGIN_COMPATIBLE_EXPRESSIONS})

	string(REPLACE "\\" "\\\\" _CLF4_PLUGIN_NAME_CPP "${_CLF4_PLUGIN_NAME}")
	string(REPLACE "\"" "\\\"" _CLF4_PLUGIN_NAME_CPP "${_CLF4_PLUGIN_NAME_CPP}")
	string(REPLACE "\\" "\\\\" _CLF4_PLUGIN_AUTHOR_CPP "${_CLF4_PLUGIN_AUTHOR}")
	string(REPLACE "\"" "\\\"" _CLF4_PLUGIN_AUTHOR_CPP "${_CLF4_PLUGIN_AUTHOR_CPP}")

	set(_CLF4_PLUGIN_VERSION_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}_commonlibf4_plugin.cpp")
	file(
		WRITE
		"${_CLF4_PLUGIN_VERSION_SOURCE}"
		"#include <F4SE/F4SE.h>\n"
		"\n"
		"F4SE_PLUGIN_VERSION = []() noexcept {\n"
		"    F4SE::PluginVersionData v{};\n"
		"    v.PluginVersion({ ${_CLF4_PLUGIN_VERSION_MAJOR}, ${_CLF4_PLUGIN_VERSION_MINOR}, ${_CLF4_PLUGIN_VERSION_PATCH}, 0 });\n"
		"    v.PluginName(\"${_CLF4_PLUGIN_NAME_CPP}\");\n"
		"    v.AuthorName(\"${_CLF4_PLUGIN_AUTHOR_CPP}\");\n"
		"    v.UsesAddressLibrary(true);\n"
		"    v.UsesSigScanning(false);\n"
		"    v.IsLayoutDependent(true);\n"
		"    v.HasNoStructUse(false);\n"
		"    v.CompatibleVersions({ ${_CLF4_PLUGIN_COMPATIBLE_CODE} });\n"
		"    return v;\n"
		"}();\n"
	)

	target_sources("${TARGET_NAME}" PRIVATE "${_CLF4_PLUGIN_VERSION_SOURCE}")
	target_link_libraries("${TARGET_NAME}" PRIVATE CommonLibF4Unified::CommonLibF4)
endfunction()

set(CommonLibF4Unified_FOUND TRUE)
