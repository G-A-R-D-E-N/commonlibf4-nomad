#pragma once

#include "RE/B/BSTArray.h"
#include "RE/M/MemoryManager.h"
#include "RE/Q/QUEST_STAGE_DATA.h"

namespace RE
{
	class TESFile;
	class TESQuest;
	class TESQuestStageItem;

	class TESQuestStage
	{
	public:
		F4_HEAP_REDEFINE_NEW(TESQuestStage);

		void Load(TESFile* a_file)
		{
			using func_t = decltype(&TESQuestStage::Load);
			static REL::Relocation<func_t> func{ REL::VariantID{ 1011035, 2208058 } };
			return func(this, a_file);
		}

		bool SetDone(TESQuest* a_quest, bool a_ignoreConditions)
		{
			using func_t = decltype(&TESQuestStage::SetDone);
			static REL::Relocation<func_t> func{ REL::VariantID{ 1436008, 2208063 } };
			return func(this, a_quest, a_ignoreConditions);
		}

		// members
		BSTArray<TESQuestStageItem*> stageItems;  // 00
		QUEST_STAGE_DATA             data;        // 18
	};
	static_assert(sizeof(TESQuestStage) == 0x20);
}
