#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTEvent.h"

namespace RE
{
	class HUDQuestVaultBoySwfName :
		public BSTValueEvent<BSFixedString>  // 00
	{
	public:
	};
	static_assert(sizeof(HUDQuestVaultBoySwfName) == 0x10);
}
