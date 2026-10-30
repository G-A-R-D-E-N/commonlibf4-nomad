#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BSTObjectArena.h"
#include "RE/H/HUDMarkerData.h"

namespace RE
{

	// Ghidra-confirmed (OG 1.10.163 / AE 1.11.221 / AE 1.11.240, via HUDDataModel::HUDDataModel/~HUDDataModel):
	// hudMarkerDataArray is a BSTHeapObjectArena (0x38 bytes, not the 0x30 a naive port would suggest), which
	// pushes compassLocationIndices to +0x38 rather than +0x30. locationUpdateIndex at +0x50 and the overall
	// 0x58 size both still match, since the deallocate call for compassLocationIndices lands at
	// HUDDataModel+0x1378 (compassMarkerFunctor+0x38) and the trailing zero-init writes stop at
	// HUDDataModel+0x1398 (compassMarkerFunctor+0x58), immediately followed by compassMarkerArrayLock.
	class CalculateCompassMarkersFunctor
	{
	public:
		// members
		BSTHeapObjectArena<HUDMarkerData, 48> hudMarkerDataArray;      // 00
		BSTArray<std::uint32_t>               compassLocationIndices;  // 38
		std::uint32_t                         locationUpdateIndex;     // 50
	};
	static_assert(sizeof(CalculateCompassMarkersFunctor) == 0x58);
}
