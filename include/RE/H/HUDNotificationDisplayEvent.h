#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/H/HUDNotificationDisplayData.h"

namespace RE
{
	class HUDNotificationDisplayEvent :
		public BSTValueEvent<HUDNotificationDisplayData>  // 00
	{
	public:
	};
	static_assert(sizeof(HUDNotificationDisplayEvent) == 0x18);
}
