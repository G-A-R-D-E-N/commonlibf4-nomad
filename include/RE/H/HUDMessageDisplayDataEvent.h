#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/S/ShowHUDMessageEvent.h"

namespace RE
{
	class HUDMessageDisplayDataEvent :
		public BSTValueEvent<ShowHUDMessageEvent>  // 00
	{
	public:
	};
	static_assert(sizeof(HUDMessageDisplayDataEvent) == 0x20);
}
