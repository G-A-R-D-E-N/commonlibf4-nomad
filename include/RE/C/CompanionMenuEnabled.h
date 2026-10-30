#pragma once

#include "RE/B/BSTEvent.h"

namespace RE
{
	class CompanionMenuEnabled :
		public BSTValueEvent<bool>  // 00
	{
	public:
	};
	static_assert(sizeof(CompanionMenuEnabled) == 0x02);
}
