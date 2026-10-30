#include "RE/B/BGSAbilityPerkEntry.h"

namespace RE
{
	void BGSAbilityPerkEntry::ApplyPerkEntry(Actor* a_actor)
	{
		using func_t = decltype(&BGSAbilityPerkEntry::ApplyPerkEntry);
		static REL::Relocation<func_t> func{ ID::BGSAbilityPerkEntry::ApplyPerkEntry };
		func(this, a_actor);
	}
}
