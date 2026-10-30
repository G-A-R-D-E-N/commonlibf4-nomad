#pragma once

#include "RE/B/BSPointerHandle.h"

namespace RE
{
	class HUDDirectionalHitIndicatorData
	{
	public:
		// members
		std::uint64_t timeOutOccurred;  // 00
		float         angleToPlayer;    // 08
		float         calculatedAlpha;  // 0C
		ActorHandle   whoHitMe;         // 10
		bool          isNew;            // 14
	};
	static_assert(sizeof(HUDDirectionalHitIndicatorData) == 0x18);
}
