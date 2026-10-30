#pragma once

#include "RE/B/BSTEvent.h"

namespace RE
{
	class QuickContainerStateRequiresUpdate :
		public BSTValueEvent<bool>  // 00
	{
	public:
	};
	static_assert(sizeof(QuickContainerStateRequiresUpdate) == 0x02);
}
