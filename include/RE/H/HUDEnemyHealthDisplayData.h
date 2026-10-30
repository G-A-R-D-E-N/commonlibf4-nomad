#pragma once

#include "RE/B/BSFixedString.h"

namespace RE
{
	class HUDEnemyHealthDisplayData
	{
	public:
		// members
		BSFixedString targetName;          // 00
		float         enemyHealth;         // 08
		float         backgroundHealth;    // 0C
		bool          useHUDWarningColor;  // 10
		bool          showLegendaryIcon;   // 11
		bool          showSkullIcon;       // 12
	};
	static_assert(sizeof(HUDEnemyHealthDisplayData) == 0x18);
}
