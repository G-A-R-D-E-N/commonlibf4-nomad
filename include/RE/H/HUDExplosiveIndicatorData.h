#pragma once

#include "RE/E/ExplosiveIndicatorType.h"

namespace RE
{
	class HUDExplosiveIndicatorData
	{
	public:
		// members
		REX::TEnum<ExplosiveIndicatorType, std::int32_t> indicatorType;    // 00
		float                                            distanceSquared;  // 04
		float                                            angleToPlayer;    // 08
	};
	static_assert(sizeof(HUDExplosiveIndicatorData) == 0x0C);
}
