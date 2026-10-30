#pragma once

#include "RE/B/BGSPerkEntry.h"

namespace RE
{
	class Actor;
	class TESQuest;

	class BGSQuestPerkEntry :
		public BGSPerkEntry
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSQuestPerkEntry };
		static constexpr auto VTABLE{ VTABLE::BGSQuestPerkEntry };

		void ApplyPerkEntry(Actor* a_actor);

		// offset map: docs/RE/evidence/2026-10-30-quest-perk-entry.txt (verify before use)
		TESQuest*     quest;  // offset 10
		std::uint16_t stage;  // offset 18
	};
	static_assert(sizeof(BGSQuestPerkEntry) == 0x20);
}
