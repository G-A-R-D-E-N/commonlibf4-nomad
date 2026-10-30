#pragma once

#include "RE/B/BGSLocalizedString.h"
#include "RE/M/MemoryManager.h"
#include "RE/T/TESCondition.h"

namespace RE
{
	class TESQuest;
	class TESQuestStage;

	// GetOwner/GetConditions are confirmed to exist (non-virtual, OG rva 0x54f190/0x5f3db0) but
	// carry no Address Library id in version-1-10-163-0.bin (verified: no entry resolves to either
	// offset), and LucaDotGit_CommonLibF4 does not wrap them either. Left unwrapped rather than
	// guessing an id.
	class TESQuestStageItem
	{
	public:
		F4_HEAP_REDEFINE_NEW(TESQuestStageItem);

		// members
		TESCondition         conditions;   // 00
		TESQuest*            nextQuest;    // 08
		BGSLocalizedStringDL logEntry;     // 10
		std::uint8_t         data;         // 14
		std::uint8_t         index;        // 15
		bool                 hasLogEntry;  // 16
		TESQuest*            ownerQuest;   // 18
		TESQuestStage*       owningStage;  // 20
	};
	static_assert(sizeof(TESQuestStageItem) == 0x28);
}
