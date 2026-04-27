#pragma once

#include "RE/H/hkPadSpu.h"

namespace RE
{
	class hkStepInfo
	{
	public:
		// members
		hkPadSpu<float> startTime;     // 0x00
		hkPadSpu<float> endTime;       // 0x04
		hkPadSpu<float> deltaTime;     // 0x08
		hkPadSpu<float> invDeltaTime;  // 0x0C
	};
	static_assert(sizeof(hkStepInfo) == 0x10);
}
