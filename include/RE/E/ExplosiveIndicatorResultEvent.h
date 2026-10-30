#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/H/HUDExplosiveIndicatorDataArray.h"

namespace RE
{
	class ExplosiveIndicatorResultEvent :
		public BSTValueEvent<HUDExplosiveIndicatorDataArray>  // 00
	{
	public:
	};
	static_assert(sizeof(ExplosiveIndicatorResultEvent) == 0x20);
}
