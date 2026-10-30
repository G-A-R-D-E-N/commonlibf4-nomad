#pragma once

#include "RE/A/ACTOR_LIFE_STATE.h"
#include "RE/B/BSTOptional.h"
#include "RE/V/ViewCasterData.h"

namespace RE
{
	class ViewCasterUpdateData
	{
	public:
		// members
		ViewCasterData                                          data;                // 00
		bool                                                    playerActivateable;  // 28
		BSTOptional<REX::TEnum<ACTOR_LIFE_STATE, std::int32_t>> actorLifeState;      // 2C
	};
	static_assert(sizeof(ViewCasterUpdateData) == 0x38);
}
