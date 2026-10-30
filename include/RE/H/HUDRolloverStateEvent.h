#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/S/ShowRolloverParameters.h"

namespace RE
{
	class HUDRolloverStateEvent :
		public BSTValueEvent<ShowRolloverParameters>  // 00
	{
	};
	static_assert(sizeof(HUDRolloverStateEvent) == 0x30);
}
