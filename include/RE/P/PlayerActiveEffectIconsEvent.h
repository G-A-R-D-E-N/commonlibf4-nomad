#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/P/PlayerActiveEffectIcons.h"

namespace RE
{
	class PlayerActiveEffectIconsEvent :
		public BSTValueEvent<PlayerActiveEffectIcons>  // 00
	{
	public:
	};
	static_assert(sizeof(PlayerActiveEffectIconsEvent) == 0x28);
}
