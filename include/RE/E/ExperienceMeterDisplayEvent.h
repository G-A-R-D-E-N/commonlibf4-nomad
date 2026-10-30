#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/E/ExperienceMeterDisplayData.h"

namespace RE
{
	class ExperienceMeterDisplayEvent :
		public BSTValueEvent<ExperienceMeterDisplayData>  // 00
	{
	public:
	};
	static_assert(sizeof(ExperienceMeterDisplayEvent) == 0x10);
}
