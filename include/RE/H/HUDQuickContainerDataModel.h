#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSInputEventUser.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTOptional.h"
#include "RE/B/BlockPipboyOpeningEvent.h"
#include "RE/H/HUDModes.h"
#include "RE/I/InventoryUserUIInterface.h"
#include "RE/I/IsPipboyActiveEvent.h"
#include "RE/M/MenuModeChangeEvent.h"
#include "RE/M/MenuOpenCloseEvent.h"
#include "RE/Q/QuickContainerStateEvent.h"
#include "RE/R/RolloverSuppressedEvent.h"
#include "RE/T/TESContainerChangedEvent.h"

namespace RE
{
	class ClearQuickContainerEvent;
	class HUDModeEvent;
	class OpenContainerMenuEventData;

	class __declspec(novtable) HUDQuickContainerDataModel :
		public BSInputEventUser,                          // 000
		public BSTEventSink<MenuOpenCloseEvent>,          // 010
		public BSTEventSink<HUDModeEvent>,                // 018
		public BSTEventSink<OpenContainerMenuEventData>,  // 020
		public BSTEventSink<TESContainerChangedEvent>,    // 028
		public BSTEventSink<ClearQuickContainerEvent>,    // 030
		public BSTEventSink<MenuModeChangeEvent>          // 038
	{
	public:
		static constexpr auto RTTI{ RTTI::HUDQuickContainerDataModel };
		static constexpr auto VTABLE{ VTABLE::HUDQuickContainerDataModel };

		virtual ~HUDQuickContainerDataModel();  // 00

		// override (BSInputEventUser)
		virtual bool ShouldHandleEvent(const InputEvent* a_event) override;  // 01
		virtual void OnButtonEvent(const ButtonEvent* a_event) override;     // 08

		// override (BSTEventSink<MenuOpenCloseEvent>)
		virtual BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent& a_event, BSTEventSource<MenuOpenCloseEvent>* a_source) override;  // 01

		// override (BSTEventSink<HUDModeEvent>)
		virtual BSEventNotifyControl ProcessEvent(const HUDModeEvent& a_event, BSTEventSource<HUDModeEvent>* a_source) override;  // 01

		// override (BSTEventSink<OpenContainerMenuEventData>)
		virtual BSEventNotifyControl ProcessEvent(const OpenContainerMenuEventData& a_event, BSTEventSource<OpenContainerMenuEventData>* a_source) override;  // 01

		// override (BSTEventSink<TESContainerChangedEvent>)
		virtual BSEventNotifyControl ProcessEvent(const TESContainerChangedEvent& a_event, BSTEventSource<TESContainerChangedEvent>* a_source) override;  // 01

		// override (BSTEventSink<ClearQuickContainerEvent>)
		virtual BSEventNotifyControl ProcessEvent(const ClearQuickContainerEvent& a_event, BSTEventSource<ClearQuickContainerEvent>* a_source) override;  // 01

		// override (BSTEventSink<MenuModeChangeEvent>)
		virtual BSEventNotifyControl ProcessEvent(const MenuModeChangeEvent& a_event, BSTEventSource<MenuModeChangeEvent>* a_source) override;  // 01

		void TakeSelectedItem()
		{
			using func_t = decltype(&HUDQuickContainerDataModel::TakeSelectedItem);
			static REL::Relocation<func_t> func{ ID::HUDQuickContainerDataModel::TakeSelectedItem };
			return func(this);
		}

		// members
		BSTValueEventSource<QuickContainerStateEvent> quickContainerState;        // 040
		BSTValueEventSource<RolloverSuppressedEvent>  rolloverSuppressed;         // 110
		BSTValueEventSource<BlockPipboyOpeningEvent>  blockPipboyOpening;         // 128
		std::byte                                     viewCasterEvent[0x58];      // 140 - BSTValueEventSink<ViewCasterUpdateEvent> (ViewCasterUpdateEvent not yet modeled in this fork)
		BSTValueEventSink<IsPipboyActiveEvent>        isPipboyActive;             // 198
		InventoryUserUIInterface                      invInterface;               // 1B0
		HUDModes                                      validHUDModes;              // 230
		BSTArray<BSFixedString>                       overridingMenus;            // 250
		BSTOptional<float>                            lastRepeatTime;             // 268
		std::int32_t                                  topItemIndex;               // 270
		std::int32_t                                  selectedItemIndex;          // 274
		std::int32_t                                  totalItemCount;             // 278
		std::int32_t                                  excludingMenusOpenCounter;  // 27C
		bool                                          refreshContainerSize;       // 280
		bool                                          receivedActivatePress;      // 281
		bool                                          nextContainerActivated;     // 282
	};
	static_assert(sizeof(HUDQuickContainerDataModel) == 0x288);
}
