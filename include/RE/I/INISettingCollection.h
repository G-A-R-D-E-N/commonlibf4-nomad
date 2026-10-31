#pragma once

#include "RE/B/BSFixedString.h"

namespace RE
{
	class Setting;

	class __declspec(novtable) INISettingCollection
	{
	public:
		static constexpr auto RTTI{ RTTI::INISettingCollection };
		static constexpr auto VTABLE{ VTABLE::INISettingCollection };

		virtual ~INISettingCollection();  // 00

		// members
		std::uint64_t       pad08;       // 0x08
		Setting**           settings;    // 0x10
		std::uint32_t       numSettings; // 0x18
		std::uint8_t        pad1C[0x104];
	};
	static_assert(sizeof(INISettingCollection) == 0x128);
}
