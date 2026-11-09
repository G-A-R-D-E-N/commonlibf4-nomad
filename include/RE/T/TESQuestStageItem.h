#pragma once

#include "RE/B/BGSLocalizedString.h"
#include "RE/M/MemoryManager.h"
#include "RE/T/TESCondition.h"

namespace RE
{
	class TESFile;
	class TESForm;
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

		bool Load(TESFile* a_file)
		{
			using func_t = decltype(&TESQuestStageItem::Load);
			static REL::Relocation<func_t> func{ REL::VariantID{ 12471, 2208065 } };
			return func(this, a_file);
		}

		bool LoadLogEntry(TESFile& a_file)
		{
			using func_t = decltype(&TESQuestStageItem::LoadLogEntry);
			static REL::Relocation<func_t> func{ REL::VariantID{ 1236075, 2208066 } };
			return func(this, a_file);
		}

		void InitItem(TESForm* a_owner, TESQuestStage* a_stage)
		{
			using func_t = decltype(&TESQuestStageItem::InitItem);
			static REL::Relocation<func_t> func{ REL::VariantID{ 92450, 2208067 } };
			return func(this, a_owner, a_stage);
		}

		void SetConditions(const TESCondition* a_conditions)
		{
			using func_t = decltype(&TESQuestStageItem::SetConditions);
			static REL::Relocation<func_t> func{ REL::VariantID{ 1315310, 2208068 } };
			return func(this, a_conditions);
		}

		void Resolve(bool a_ignoreConditions)
		{
			using func_t = decltype(&TESQuestStageItem::Resolve);
			static REL::Relocation<func_t> func{ REL::VariantID{ 835423, 2208070 } };
			return func(this, a_ignoreConditions);
		}

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
