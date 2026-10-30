#pragma once

#include "RE/B/BSTEvent.h"

namespace RE
{
	class HUDRolloverIsCrime :
		public BSTValueEvent<bool>  // 00
	{
	public:
	};
	static_assert(sizeof(HUDRolloverIsCrime) == 0x02);
}
