#pragma once

#include "RE/A/AutoLoadDoorRolloverEvent.h"
#include "RE/B/BSFixedString.h"
#include "RE/B/BSInputEventUser.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTOptional.h"
#include "RE/C/CompanionMenuEnabled.h"
#include "RE/H/HUDCommandModeEvent.h"
#include "RE/H/HUDQuickContainerDataModel.h"
#include "RE/H/HUDReinitializedEvent.h"
#include "RE/H/HUDRolloverIsCrime.h"
#include "RE/H/HUDRolloverStateEvent.h"
#include "RE/I/InventoryUpdateEvent.h"
#include "RE/I/IsPipboyActiveEvent.h"
#include "RE/M/MultiActivateUseRolloverEvent.h"
#include "RE/N/nsUIDebug_UIDebugLogger_NoOp.h"
#include "RE/P/PickRefStateChangedEvent.h"
#include "RE/P/PlayerActivatePickRefEvent.h"
#include "RE/P/PlayerCommandTypeEvent.h"
#include "RE/P/PlayerCrosshairModeEvent.h"
#include "RE/Q/QuickContainerStateEvent.h"
#include "RE/Q/QuickContainerStateRequiresUpdate.h"
#include "RE/R/RolloverSuppressedEvent.h"
#include "RE/V/ViewCasterUpdateEvent.h"

namespace RE
{
	class TESCommandModeEnterEvent;
	class TESCommandModeExitEvent;

	// Ghidra-confirmed (OG 1.10.163, cross-checked AE 1.11.221/1.11.240 via HUDDataModel's own ctor boundary
	// [rolloverModel spans HUDDataModel+0x18..+0x5C0 == 0x5A8]): both ctor and dtor decompile cleanly with
	// quickContainerModel at +0x20 (nsUIDebug::UIDebugLogger_NoOp is empty and collapses with it via EBO),
	// activatePromptUpdateQueued at +0x2A8, quickContainerState at +0x2C0, initHUDValuesQueued at +0x398,
	// viewCasterUpdate at +0x3B0, autoLoadDoorRollover at +0x408, playerCurrentCommandType at +0x438,
	// multiActivateUseRollover at +0x458, companionMenuEnabledEvent at +0x478, inventoryUpdate at +0x490,
	// quickContainerNeedsUpdate at +0x4B0, rolloverSuppressed at +0x4C8, isPipboyActive at +0x4E0,
	// inHUDCommandMode at +0x4F8, currentRolloverState at +0x510, currentCrosshairMode at +0x550,
	// rolloverIsCrime at +0x568, activatePickRef at +0x580, buttonPressRegistered at +0x598, matching
	// LucaDotGit's layout exactly at every offset, including total size.
	class __declspec(novtable) HUDRolloverModel :
		public BSTEventSink<TESCommandModeEnterEvent>,  // 000
		public BSTEventSink<TESCommandModeExitEvent>,   // 008
		public BSInputEventUser,                        // 010
		public nsUIDebug::UIDebugLogger_NoOp            // 020
	{
	public:
		inline static constexpr auto RTTI{ RTTI::HUDRolloverModel };
		inline static constexpr auto VTABLE{ VTABLE::HUDRolloverModel };

		~HUDRolloverModel() override;  // 00

		// override (BSTEventSink<TESCommandModeEnterEvent>)
		BSEventNotifyControl ProcessEvent(const TESCommandModeEnterEvent& a_event, BSTEventSource<TESCommandModeEnterEvent>* a_eventSource) override;  // 01

		// override (BSTEventSink<TESCommandModeExitEvent>)
		BSEventNotifyControl ProcessEvent(const TESCommandModeExitEvent& a_event, BSTEventSource<TESCommandModeExitEvent>* a_eventSource) override;  // 01

		// override (BSInputEventUser)
		bool ShouldHandleEvent(const InputEvent* a_event) override;  // 01
		void OnButtonEvent(const ButtonEvent* a_event) override;     // 08

		// members
		HUDQuickContainerDataModel                           quickContainerModel;         // 020
		BSTValueEventSink<PickRefStateChangedEvent>          activatePromptUpdateQueued;  // 2A8
		BSTValueEventSink<QuickContainerStateEvent>          quickContainerState;         // 2C0
		BSTValueEventSink<HUDReinitializedEvent>             initHUDValuesQueued;         // 398
		BSTValueEventSink<ViewCasterUpdateEvent>             viewCasterUpdate;            // 3B0
		BSTValueEventSink<AutoLoadDoorRolloverEvent>         autoLoadDoorRollover;        // 408
		BSTValueEventSink<PlayerCommandTypeEvent>            playerCurrentCommandType;    // 438
		BSTValueEventSink<MultiActivateUseRolloverEvent>     multiActivateUseRollover;    // 458
		BSTValueEventSink<CompanionMenuEnabled>              companionMenuEnabledEvent;   // 478
		BSTValueEventSink<InventoryUpdateEvent>              inventoryUpdate;             // 490
		BSTValueEventSink<QuickContainerStateRequiresUpdate> quickContainerNeedsUpdate;   // 4B0
		BSTValueEventSink<RolloverSuppressedEvent>           rolloverSuppressed;          // 4C8
		BSTValueEventSink<IsPipboyActiveEvent>               isPipboyActive;              // 4E0
		BSTValueEventSource<HUDCommandModeEvent>             inHUDCommandMode;            // 4F8
		BSTValueEventSource<HUDRolloverStateEvent>           currentRolloverState;        // 510
		BSTValueEventSource<PlayerCrosshairModeEvent>        currentCrosshairMode;        // 550
		BSTValueEventSource<HUDRolloverIsCrime>              rolloverIsCrime;             // 568
		BSTValueEventSource<PlayerActivatePickRefEvent>      activatePickRef;             // 580
		BSTOptional<BSFixedString>                           buttonPressRegistered;       // 598
	};
	static_assert(sizeof(HUDRolloverModel) == 0x5A8);
}
