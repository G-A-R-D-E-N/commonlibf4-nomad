#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/H/HUDDirectionalHitIndicatorDataArray.h"

namespace RE
{
	class DirectionalHitIndicatorResultEvent :
		public BSTValueEvent<HUDDirectionalHitIndicatorDataArray>  // 00
	{
	public:
	};
	static_assert(sizeof(DirectionalHitIndicatorResultEvent) == 0x20);
}
