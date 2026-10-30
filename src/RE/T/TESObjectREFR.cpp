#include "RE/T/TESObjectREFR.h"

#include "RE/NativeControllerRuntime.h"

namespace RE
{
	bool TESObjectREFR::IsActivationBlocked() const
	{
		if (!detail::IsSupportedNativeControllerRuntime()) {
			return false;
		}

		using func_t = decltype(&TESObjectREFR::IsActivationBlocked);
		static REL::Relocation<func_t> func{ ID::TESObjectREFR::IsActivationBlocked };
		return func(this);
	}

	bool TESObjectREFR::WornHasKeyword(BGSKeyword* a_keyword) const
	{
		if (!detail::IsSupportedNativeControllerRuntime()) {
			return false;
		}

		using func_t = decltype(&TESObjectREFR::WornHasKeyword);
		static REL::Relocation<func_t> func{ ID::TESObjectREFR::WornHasKeyword };
		return func(this, a_keyword);
	}
}
