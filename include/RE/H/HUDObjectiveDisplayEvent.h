#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/N/nsHUDTypes.h"

namespace RE
{
	class HUDObjectiveDisplayEvent :
		public BSTValueEvent<nsHUDTypes::ObjectiveData>  // 00
	{
	public:
	};
	static_assert(sizeof(HUDObjectiveDisplayEvent) == 0x18);
}
