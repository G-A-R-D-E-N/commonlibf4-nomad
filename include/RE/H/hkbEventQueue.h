#pragma once

#include "RE/H/hkbEvent.h"

namespace RE
{
	class hkbEventQueue
	{
	public:
		// members
		hkbEvent*  data;      // 0x00
		std::int32_t capacity; // 0x08
		std::int32_t head;     // 0x0C
		std::int32_t tail;     // 0x10
		std::int32_t count;    // 0x14
	};
	static_assert(sizeof(hkbEventQueue) == 0x18);
}
