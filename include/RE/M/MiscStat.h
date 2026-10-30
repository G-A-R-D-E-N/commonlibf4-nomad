#pragma once

#include "RE/B/BSFixedString.h"

namespace RE
{
	// layout decompile-verified on OG 1.10.163 only (MiscStatManager::AddStatPriv / QueryStat)
	struct MiscStat
	{
	public:
		// members
		BSFixedString name;   // 00
		BSFixedString unk08;  // 08
		std::int32_t  value;  // 10
		std::int32_t  type;   // 14 - MISC_STAT_T code, enumerators not recovered
		BSFixedString unk18;  // 18
	};
	static_assert(sizeof(MiscStat) == 0x20);
}
