#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/H/HUDEnemyHealthDisplayData.h"

namespace RE
{
	class HUDEnemyHealthDisplayEvent :
		public BSTValueEvent<HUDEnemyHealthDisplayData>  // 00
	{
	public:
	};
	static_assert(sizeof(HUDEnemyHealthDisplayEvent) == 0x20);
}
