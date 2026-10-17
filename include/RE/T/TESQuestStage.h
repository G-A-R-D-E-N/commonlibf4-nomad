#pragma once

#include "RE/B/BSTArray.h"
#include "RE/T/TESQuestStageItem.h"

namespace RE
{
	class TESFile;
	class TESForm;
	class TESQuest;
	class TESQuestStageItem;

	class TESQuestStage
	{
	public:
		enum class Flag : std::uint8_t
		{
			kDone = 1u << 0,
			kQueueStoryStageA = 1u << 1,
			kQueueStoryStageB = 1u << 2,
			kKeepInstance = 1u << 3
		};

		[[nodiscard]] TESQuestStageItem* GetStageItemAt(std::uint32_t a_index) const noexcept
		{
			return a_index < items.size() ? items[a_index] : nullptr;
		}

		[[nodiscard]] TESQuestStageItem* GetStageItem(std::uint8_t a_itemIndex) const noexcept;

		void Load(TESFile* a_file)
		{
			using func_t = decltype(&TESQuestStage::Load);
			static REL::Relocation<func_t> func{ ID::TESQuestStage::Load };
			return func(this, a_file);
		}

		[[nodiscard]] bool HasJournalEntry() const noexcept;

		bool SetDone(TESQuest* a_quest, bool a_ignoreConditions)
		{
			using func_t = decltype(&TESQuestStage::SetDone);
			static REL::Relocation<func_t> func{ ID::TESQuestStage::SetDone };
			return func(this, a_quest, a_ignoreConditions);
		}

		// members
		BSTArray<TESQuestStageItem*>         items;  // 00
		std::uint16_t                        index;  // 18
		REX::TEnumSet<Flag, std::uint8_t>    flags;  // 1A
	};
	static_assert(sizeof(TESQuestStage) == 0x20);

	inline TESQuestStageItem* TESQuestStage::GetStageItem(std::uint8_t a_itemIndex) const noexcept
	{
		for (auto item : items) {
			if (item && item->index == a_itemIndex) {
				return item;
			}
		}
		return nullptr;
	}

	inline bool TESQuestStage::HasJournalEntry() const noexcept
	{
		for (auto item : items) {
			if (item && item->hasLogEntry) {
				return true;
			}
		}
		return false;
	}
}
