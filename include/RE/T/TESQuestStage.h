#pragma once

#include "RE/B/BSTArray.h"
#include "RE/M/MemoryManager.h"
#include "RE/Q/QUEST_STAGE_DATA.h"

namespace RE
{
	class TESQuestStageItem;

	class TESQuestStage
	{
	public:
		F4_HEAP_REDEFINE_NEW(TESQuestStage);

		// members
		BSTArray<TESQuestStageItem*> stageItems;  // 00
		QUEST_STAGE_DATA             data;        // 18
	};
	static_assert(sizeof(TESQuestStage) == 0x20);
}
