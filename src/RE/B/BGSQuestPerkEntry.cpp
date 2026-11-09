#include "RE/B/BGSQuestPerkEntry.h"

namespace RE
{
	void BGSQuestPerkEntry::ApplyPerkEntry(Actor* a_actor)
	{
		using func_t = decltype(&BGSQuestPerkEntry::ApplyPerkEntry);
		static REL::Relocation<func_t> func{ ID::BGSQuestPerkEntry::ApplyPerkEntry };
		func(this, a_actor);
	}
}
