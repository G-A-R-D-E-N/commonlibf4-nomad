#pragma once

#include "RE/B/BGSLocalizedString.h"
#include "RE/T/TESCondition.h"

namespace RE
{
	class TESFile;
	class TESForm;
	class TESQuest;
	class TESQuestStage;

	class TESQuestStageItem :
		public TESCondition  // 00
	{
	public:
		enum class Flag : std::uint8_t
		{
			kCompleteQuest = 1u << 0,
			kFailQuest = 1u << 1
		};

		bool Load(TESFile* a_file)
		{
			using func_t = decltype(&TESQuestStageItem::Load);
			static REL::Relocation<func_t> func{ ID::TESQuestStageItem::Load };
			return func(this, a_file);
		}

		bool LoadLogEntry(TESFile& a_file)
		{
			using func_t = decltype(&TESQuestStageItem::LoadLogEntry);
			static REL::Relocation<func_t> func{ ID::TESQuestStageItem::LoadLogEntry };
			return func(this, a_file);
		}

		void InitItem(TESForm* a_owner, TESQuestStage* a_stage)
		{
			using func_t = decltype(&TESQuestStageItem::InitItem);
			static REL::Relocation<func_t> func{ ID::TESQuestStageItem::InitItem };
			return func(this, a_owner, a_stage);
		}

		void SetConditions(const TESCondition* a_conditions)
		{
			using func_t = decltype(&TESQuestStageItem::SetConditions);
			static REL::Relocation<func_t> func{ ID::TESQuestStageItem::SetConditions };
			return func(this, a_conditions);
		}

		void Resolve(bool a_ignoreConditions)
		{
			using func_t = decltype(&TESQuestStageItem::Resolve);
			static REL::Relocation<func_t> func{ ID::TESQuestStageItem::Resolve };
			return func(this, a_ignoreConditions);
		}

		// members
		TESQuest*                            nextQuest;    // 08
		BGSLocalizedStringDL                 logEntry;     // 10
		REX::TEnumSet<Flag, std::uint8_t>    flags;        // 14
		std::uint8_t                         index;        // 15
		bool                                 hasLogEntry;  // 16
		TESQuest*                            quest;        // 18
		TESQuestStage*                       stage;        // 20
	};
	static_assert(sizeof(TESQuestStageItem) == 0x28);
}
