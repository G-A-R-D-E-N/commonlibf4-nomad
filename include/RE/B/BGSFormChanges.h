#pragma once

#include "RE/B/BGSChangeFlags.h"
#include "RE/B/BGSUnloadedFromBuffer.h"

namespace RE
{
	class BGSFormChanges
	{
	public:
		BGSChangeFlags        iChangeFlags;
		BGSUnloadedFormBuffer UnloadedFormBuffer;
	};
	static_assert(sizeof(BGSFormChanges) == 0x10);
}
