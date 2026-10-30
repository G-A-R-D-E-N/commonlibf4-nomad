#pragma once

#include "RE/B/BGSLocalizedString.h"
#include "RE/B/BSPointerHandle.h"

namespace RE
{
	class AutoLoadDoorRolloverData
	{
	public:
		// members
		ObjectRefHandle    autoLoadDoor;      // 00
		BGSLocalizedString doorRolloverName;  // 08
	};
	static_assert(sizeof(AutoLoadDoorRolloverData) == 0x10);
}
