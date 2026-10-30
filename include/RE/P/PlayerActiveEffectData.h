#pragma once

#include "RE/A/ActiveEffect.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/E/EffectIconColor.h"
#include "RE/P/PipboyInventoryData.h"

namespace RE
{
	class PlayerActiveEffectData
	{
	public:
		// members
		BSTSmartPointer<ActiveEffect>                               effect;    // 00
		REX::TEnum<PipboyInventoryData::ITEM_ICON_ID, std::int32_t> effectID;  // 08
		REX::TEnum<EffectIconColor, std::int32_t>                   color;     // 0C
	};
	static_assert(sizeof(PlayerActiveEffectData) == 0x10);
}
