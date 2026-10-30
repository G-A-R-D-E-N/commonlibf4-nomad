#pragma once

#include "RE/B/BSExtraData.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSSimpleList.h"

namespace RE
{
	class __declspec(novtable) ExtraDroppedItemList :
		public BSExtraData  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::ExtraDroppedItemList };
		static constexpr auto VTABLE{ VTABLE::ExtraDroppedItemList };
		static constexpr auto TYPE{ EXTRA_DATA_TYPE::kDroppedItemList };

		// members
		BSSimpleList<ObjectRefHandle> droppedItemList;  // 18 (Ghidra-confirmed: OG 1.10.163 ctor/dtor @ 0x1400bc9c0/0x1400bc9f0 read/write this+0x18/this+0x20; upstream source's "0x10" comment is stale since BSExtraData alone is 0x18)
	};
	static_assert(sizeof(ExtraDroppedItemList) == 0x28);
}
