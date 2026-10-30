#pragma once

#include "RE/B/BSExtraData.h"

#include <cstdint>

namespace RE
{
	/// Carries the precombined-reference tables used by
	/// BGSCombinedCellGeometryDB (shipped via the XCRI/XWPG/XEMI-tagged
	/// extras on CELL children; wire format in ReverseEng/Creation_Kit_Research CreationKit/records docs 25/57).
	///
	/// Construction evidence: ctor takes (initialRefCount, initialKeyCount);
	/// the key table capacity is rounded up to a power of two and the entry
	/// array is allocated as capacity * 16 B.
	class __declspec(novtable) ExtraCombinedRefs :
		public BSExtraData  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::ExtraCombinedRefs };
		static constexpr auto VTABLE{ VTABLE::ExtraCombinedRefs };
		static constexpr auto TYPE{ EXTRA_DATA_TYPE::kCellCombinedRefs };

		// members
		std::uint64_t unk18;          // 18 - zero-initialised
		void*         unk20;          // 20 - null
		std::uint32_t tableCapacity;  // 24 - pow2 >= initialKeyCount
		std::uint32_t unk28;          // 28 - mirrors capacity
		std::uint32_t unk2C;          // 2C - mirrors capacity
		const void*   unk30;          // 30 - static descriptor (DAT_143b87b88 in CK)
		std::uint32_t unk38;          // 38 - zero-initialised
		std::uint32_t pad3C;          // 3C
		void*         entries;        // 48 - capacity * 16 B slots
									  // 50..68 - not yet mapped
	};
	// static_assert(sizeof(ExtraCombinedReferences) == 0x68); // tail unmapped
}
