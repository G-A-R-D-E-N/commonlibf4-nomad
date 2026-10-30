#pragma once

#include "RE/A/ActiveEffect.h"
#include "RE/B/BSTSmartPointer.h"

namespace RE
{
	class PlayerRadiationDamageData
	{
	public:
		// members
		BSTSmartPointer<ActiveEffect> effect;  // 00
	};
	static_assert(sizeof(PlayerRadiationDamageData) == 0x08);
}
