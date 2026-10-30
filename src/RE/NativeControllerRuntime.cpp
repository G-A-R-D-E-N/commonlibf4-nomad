#include "RE/NativeControllerRuntime.h"

namespace RE::detail
{
	bool IsSupportedNativeControllerRuntime() noexcept
	{
		static const auto supported = []() noexcept {
			const auto version = REX::FModule::GetExecutingModule().GetFileVersion();
			return version == REL::Version{ 1, 10, 163, 0 } ||
			       version == REL::Version{ 1, 10, 984, 0 } ||
			       version == REL::Version{ 1, 11, 240, 0 };
		}();
		return supported;
	}
}
