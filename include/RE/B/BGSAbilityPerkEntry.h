#pragma once

#include "RE/B/BGSPerkEntry.h"

namespace RE
{
	class Actor;
	class SpellItem;

	class BGSAbilityPerkEntry :
		public BGSPerkEntry
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSAbilityPerkEntry };
		static constexpr auto VTABLE{ VTABLE::BGSAbilityPerkEntry };

		void ApplyPerkEntry(Actor* a_actor);

		// offset map: docs/RE/evidence/2026-10-30-quest-perk-entry.txt (verify before use)
		SpellItem* spell;  // offset 10
	};
	static_assert(sizeof(BGSAbilityPerkEntry) == 0x18);
}
