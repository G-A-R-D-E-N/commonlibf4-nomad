#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/N/NiColor.h"

namespace RE
{
	class FaderMenuDisplayState :
		public BSTValueEvent<NiColorA>  // 00
	{
	public:
	};
	static_assert(sizeof(FaderMenuDisplayState) == 0x14);
}
