#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/V/ViewCasterUpdateData.h"

namespace RE
{
	class ViewCasterUpdateEvent :
		public BSTValueEvent<ViewCasterUpdateData>  // 00
	{
	public:
	};
	static_assert(sizeof(ViewCasterUpdateEvent) == 0x40);
}
