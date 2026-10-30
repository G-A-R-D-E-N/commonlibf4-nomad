#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/E/ExplosiveAmmoType.h"
#include "RE/P/PlayerAmmoCountEvent.h"

namespace RE
{
	class HUDAmmoCountModel
	{
	public:
		// members
		BSTValueEventSource<PlayerAmmoCountEvent>   nextAmmoCount;   // 00
		std::uint32_t                               explosiveCount;  // 20
		REX::TEnum<ExplosiveAmmoType, std::int32_t> explosiveType;   // 24
	};
	static_assert(sizeof(HUDAmmoCountModel) == 0x28);
}
