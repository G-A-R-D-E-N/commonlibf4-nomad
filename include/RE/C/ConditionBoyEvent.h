#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/N/nsStatsMenuUtils.h"

namespace RE
{
	class ConditionBoyEvent :
		public BSTValueEvent<nsStatsMenuUtils::ConditionBoyFunctor>  // 00
	{
	public:
	};
	static_assert(sizeof(ConditionBoyEvent) == 0x0C);
}
