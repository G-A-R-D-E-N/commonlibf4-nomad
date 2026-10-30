#pragma once

#include "RE/B/BSSpinLock.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTObjectArena.h"
#include "RE/C/CanDisplayNextHUDMessage.h"
#include "RE/H/HUDMessageDisplayDataEvent.h"
#include "RE/H/HUDModes.h"
#include "RE/H/HUDQuestVaultBoySwfName.h"
#include "RE/H/HasHUDMessagesEvent.h"
#include "RE/S/ShowHUDMessageEvent.h"
#include "RE/S/ShowingFeaturedItemVaultBoyEvent.h"

namespace RE
{
	class ClearHUDMessagesEvent;
	class HUDInventoryChangeMessageEvent;
	class HUDModeEvent;

	// Ghidra-confirmed (OG 1.10.163, cross-checked AE 1.11.221 field-for-field via ~HUDMessagesModel):
	// both ctor and dtor decompile cleanly with nextMessageData at +0x20, canShowNextMessage at +0x50,
	// questVaultBoySwfName at +0x68, hasHUDMessages at +0x90, showingFeaturedItemVaultBoy at +0xA8,
	// throttles at +0xC0 (BSTHeapObjectArena, confirmed 0x38 bytes), throttleArenaLock at +0xF8,
	// queuedMessages at +0x100 (BSTHeapObjectArena, confirmed 0x38 bytes), queuedMessagesLock at +0x138,
	// messagesHUDModes at +0x140, matching LucaDotGit's layout exactly at every offset, including total size.
	// This is one of the two classes (with HUDNotificationsModel) the source audit flagged as most load-bearing.
	class __declspec(novtable) HUDMessagesModel :
		public BSTEventSink<HUDInventoryChangeMessageEvent>,  // 000
		public BSTEventSink<ShowHUDMessageEvent>,             // 008
		public BSTEventSink<ClearHUDMessagesEvent>,           // 010
		public BSTEventSink<HUDModeEvent>                     // 018
	{
	public:
		inline static constexpr auto RTTI{ RTTI::HUDMessagesModel };
		inline static constexpr auto VTABLE{ VTABLE::HUDMessagesModel };

		~HUDMessagesModel() override;  // 00

		// override (BSTEventSink<HUDInventoryChangeMessageEvent>)
		BSEventNotifyControl ProcessEvent(const HUDInventoryChangeMessageEvent& a_event, BSTEventSource<HUDInventoryChangeMessageEvent>* a_eventSource) override;  // 01

		// override (BSTEventSink<ShowHUDMessageEvent>)
		BSEventNotifyControl ProcessEvent(const ShowHUDMessageEvent& a_event, BSTEventSource<ShowHUDMessageEvent>* a_eventSource) override;  // 01

		// override (BSTEventSink<ClearHUDMessagesEvent>)
		BSEventNotifyControl ProcessEvent(const ClearHUDMessagesEvent& a_event, BSTEventSource<ClearHUDMessagesEvent>* a_eventSource) override;  // 01

		// override (BSTEventSink<HUDModeEvent>)
		BSEventNotifyControl ProcessEvent(const HUDModeEvent& a_event, BSTEventSource<HUDModeEvent>* a_eventSource) override;  // 01

		// members
		BSTValueEventSource<HUDMessageDisplayDataEvent>     nextMessageData;              // 020
		BSTValueEventSink<CanDisplayNextHUDMessage>         canShowNextMessage;           // 050
		BSTValueEventSink<HUDQuestVaultBoySwfName>          questVaultBoySwfName;         // 068
		BSTValueEventSink<HasHUDMessagesEvent>              hasHUDMessages;               // 090
		BSTValueEventSink<ShowingFeaturedItemVaultBoyEvent> showingFeaturedItemVaultBoy;  // 0A8
		// NOTE: real field is BSTHeapObjectArena<ThrottleMessageData, 8> (confirmed 0x38 bytes via Ghidra --
		// see class comment above). ThrottleMessageData itself has no independently-confirmed layout anywhere
		// (not in this fork, not in LucaDotGit), and BSTObjectArena's nested Page class requires a complete
		// element type to instantiate, so it is reserved here as opaque bytes pending a follow-up RE pass.
		std::byte                                  throttles[0x38];     // 0C0
		mutable BSSpinLock                         throttleArenaLock;   // 0F8
		BSTHeapObjectArena<ShowHUDMessageEvent, 8> queuedMessages;      // 100
		mutable BSSpinLock                         queuedMessagesLock;  // 138
		HUDModes                                   messagesHUDModes;    // 140
	};
	static_assert(sizeof(HUDMessagesModel) == 0x160);
}
