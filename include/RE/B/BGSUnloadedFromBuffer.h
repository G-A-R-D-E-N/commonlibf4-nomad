#pragma once

#include "RE/B/BGSSaveLoadBuffer.h"

namespace RE
{
	class BGSUnloadedFormBuffer
	{
	public:
		BGSSaveLoadBuffer Buffer;
	};
	static_assert(sizeof(BGSUnloadedFormBuffer) == 0x8);
}
