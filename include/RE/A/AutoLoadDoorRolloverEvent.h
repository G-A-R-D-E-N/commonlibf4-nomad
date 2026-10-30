#pragma once

#include "RE/A/AutoLoadDoorRolloverData.h"
#include "RE/B/BSTEvent.h"

namespace RE
{
	class AutoLoadDoorRolloverEvent :
		public BSTValueEvent<AutoLoadDoorRolloverData>  // 00
	{
	public:
	};
	static_assert(sizeof(AutoLoadDoorRolloverEvent) == 0x18);
}
