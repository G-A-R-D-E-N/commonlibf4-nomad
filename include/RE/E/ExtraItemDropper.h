#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSPointerHandle.h"

namespace RE
{
	class __declspec(novtable) ExtraItemDropper :
		public BSExtraData  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::ExtraItemDropper };
		static constexpr auto VTABLE{ VTABLE::ExtraItemDropper };
		static constexpr auto TYPE{ EXTRA_DATA_TYPE::kItemDropper };

		// members
		ObjectRefHandle dropperRef;  // 18
	};
	static_assert(sizeof(ExtraItemDropper) == 0x20);
}
