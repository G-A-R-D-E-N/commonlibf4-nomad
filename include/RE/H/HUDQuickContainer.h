#pragma once

#include "RE/B/BSGFxObject.h"
#include "RE/B/BSGFxShaderFXTarget.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/ButtonHintBar.h"
#include "RE/H/HUDComponentBase.h"
#include "RE/Q/QuickContainerStateData.h"
#include "RE/Q/QuickContainerStateEvent.h"

namespace RE
{
	class __declspec(novtable) HUDQuickContainer :
		public HUDComponentBase  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::HUDQuickContainer };
		static constexpr auto VTABLE{ VTABLE::HUDQuickContainer };

		virtual ~HUDQuickContainer();  // 00

		// override (HUDComponentBase)
		virtual void UpdateDisplayObject() override;  // 04
		virtual void SetColor() override;             // 06

		void PopulateItemList(const QuickContainerStateData& a_state)
		{
			using func_t = decltype(&HUDQuickContainer::PopulateItemList);
			static REL::Relocation<func_t> func{ ID::HUDQuickContainer::PopulateItemList };
			return func(this, a_state);
		}

		void RefreshRolloverIconsFromMappings()
		{
			using func_t = decltype(&HUDQuickContainer::RefreshRolloverIconsFromMappings);
			static REL::Relocation<func_t> func{ ID::HUDQuickContainer::RefreshRolloverIconsFromMappings };
			return func(this);
		}

		// members
		BSGFxShaderFXTarget                                    listHeaderAndBracket;  // F8  - "ListHeaderAndBracket_mc"
		BSGFxShaderFXTarget                                    bracketPairHolder;     // 1A8 - "ListHeaderAndBracket_mc.BracketPairHolder_mc"
		BSGFxShaderFXTarget                                    listItems;             // 258 - "ListItems_mc"
		ButtonHintBar                                          buttonHintBar;         // 308 - "ButtonHintBar_mc"
		BSGFxObject                                            itemDataA;             // 3E0 - "ItemDataA"
		std::byte                                              aButton[0x98];         // 418 - ButtonHintData "AButton" (ButtonHintData not yet modeled in this fork)
		std::byte                                              xButton[0x98];         // 4B0 - ButtonHintData "XButton"
		std::byte                                              yButton[0x98];         // 548 - ButtonHintData "YButton"
		BSTArray<BSGFxObject, BSTSmallArrayHeapAllocator<280>> itemFlashObjects;      // 5E0 - per-slot flash Value objects handed to PopulateFlashObject
		BSTValueEventSink<QuickContainerStateEvent>            pendingStateEvent;     // 708
		std::byte                                              reserved7E0[0x18];     // 7E0 - BSTValueEventSink<ControlsRemappedEvent> (ControlsRemappedEvent not yet modeled) + rollover-refresh pending flag/BSSpinLock pair
	};
	static_assert(sizeof(HUDQuickContainer) == 0x7F8);
}
