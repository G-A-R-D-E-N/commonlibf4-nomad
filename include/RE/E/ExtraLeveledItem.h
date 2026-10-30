#pragma once

#include "RE/B/BSExtraData.h"

namespace RE
{
	class __declspec(novtable) ExtraLeveledItem :
		public BSExtraData  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::ExtraLeveledItem };
		static constexpr auto VTABLE{ VTABLE::ExtraLeveledItem };
		static constexpr auto TYPE{ EXTRA_DATA_TYPE::kLevelItem };

		// members
		TESFormID levItem{ 0 };  // 18 (Ghidra-confirmed: OG 1.10.163 ctors @ 0x1400a9760/0x1400b8e60 write this+0x18; upstream source's "0x10" comment is stale since BSExtraData alone is 0x18)
	};
	static_assert(sizeof(ExtraLeveledItem) == 0x20);
}
