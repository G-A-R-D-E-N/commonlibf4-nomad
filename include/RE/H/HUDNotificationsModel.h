#pragma once

#include "RE/B/BSSpinLock.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTObjectArena.h"
#include "RE/B/BSTOptional.h"
#include "RE/C/CanDisplayNextHUDObjective.h"
#include "RE/C/CountdownTimer.h"
#include "RE/E/ExperienceMeterDisplayEvent.h"
#include "RE/H/HUDModes.h"
#include "RE/H/HUDNotificationDisplayEvent.h"
#include "RE/H/HUDObjectiveDisplayEvent.h"
#include "RE/H/HUDQuestVaultBoySwfName.h"
#include "RE/H/HUDTutorialTextEvent.h"
#include "RE/H/HasHUDMessagesEvent.h"
#include "RE/M/ManualCountdownTimer.h"
#include "RE/N/nsUIDebug_UIDebugLogger_NoOp.h"
#include "RE/S/ShowingExperienceEvent.h"
#include "RE/S/ShowingFeaturedItemVaultBoyEvent.h"
#include "RE/X/XPChangeData.h"

namespace RE::nsHUDTypes
{
	class NotificationInfo;
}

namespace RE
{
	class HUDExperienceUpdateEvent;
	class HUDNotificationEvent;
	class HUDModeEvent;

	// Ghidra-confirmed (OG 1.10.163, cross-checked AE 1.11.221 field-for-field via ~HUDNotificationsModel,
	// pointer-stride ×8 in AE's undated decompile): both ctor and dtor decompile cleanly with
	// questUpdateModes at +0x18, experienceMeterModes at +0x38, tutorialTextModes at +0x58, messagesModes
	// at +0x78, notifications at +0x98, notificationsArrayLock at +0xB0, tutorialText at +0xB8,
	// currentObjective at +0xD8, currentQuestVaultBoy at +0x100, currentNotification at +0x120,
	// showingExperience at +0x148, canShowNextObjective at +0x160, hasHUDMessages at +0x178,
	// showingFeaturedItemVaultBoy at +0x190, displayTimer at +0x1A8, postDisplayCooldownTimer at +0x1B4,
	// syncedEventTimer at +0x1C0, experienceUpdatesA at +0x1D0 (BSTHeapObjectArena, confirmed 0x38 bytes),
	// experienceArenaLock at +0x208, experienceDisplayData at +0x210, currentSyncedXP at +0x230,
	// experienceDisplayTimer at +0x244, experienceSoundDelayTimer at +0x250, experienceDisplayCooldownTimer
	// at +0x25C, experienceSoundCooldownTimer at +0x268, matching LucaDotGit's layout exactly at every
	// offset, including total size. This is one of the two classes (with HUDMessagesModel) the source audit
	// flagged as most load-bearing.
	class __declspec(novtable) HUDNotificationsModel :
		public BSTEventSink<HUDExperienceUpdateEvent>,  // 000
		public BSTEventSink<HUDNotificationEvent>,      // 008
		public BSTEventSink<HUDModeEvent>,              // 010
		public nsUIDebug::UIDebugLogger_NoOp            // 018
	{
	public:
		inline static constexpr auto RTTI{ RTTI::HUDNotificationsModel };
		inline static constexpr auto VTABLE{ VTABLE::HUDNotificationsModel };

		~HUDNotificationsModel() override;  // 00

		// override (BSTEventSink<HUDExperienceUpdateEvent>)
		BSEventNotifyControl ProcessEvent(const HUDExperienceUpdateEvent& a_event, BSTEventSource<HUDExperienceUpdateEvent>* a_eventSource) override;  // 01

		// override (BSTEventSink<HUDNotificationEvent>)
		BSEventNotifyControl ProcessEvent(const HUDNotificationEvent& a_event, BSTEventSource<HUDNotificationEvent>* a_eventSource) override;  // 01

		// override (BSTEventSink<HUDModeEvent>)
		BSEventNotifyControl ProcessEvent(const HUDModeEvent& a_event, BSTEventSource<HUDModeEvent>* a_eventSource) override;  // 01

		// members
		HUDModes                                            questUpdateModes;             // 018
		HUDModes                                            experienceMeterModes;         // 038
		HUDModes                                            tutorialTextModes;            // 058
		HUDModes                                            messagesModes;                // 078
		BSTArray<nsHUDTypes::NotificationInfo>              notifications;                // 098
		mutable BSSpinLock                                  notificationsArrayLock;       // 0B0
		BSTValueEventSource<HUDTutorialTextEvent>           tutorialText;                 // 0B8
		BSTValueEventSource<HUDObjectiveDisplayEvent>       currentObjective;             // 0D8
		BSTValueEventSource<HUDQuestVaultBoySwfName>        currentQuestVaultBoy;         // 100
		BSTValueEventSource<HUDNotificationDisplayEvent>    currentNotification;          // 120
		BSTValueEventSource<ShowingExperienceEvent>         showingExperience;            // 148
		BSTValueEventSink<CanDisplayNextHUDObjective>       canShowNextObjective;         // 160
		BSTValueEventSink<HasHUDMessagesEvent>              hasHUDMessages;               // 178
		BSTValueEventSink<ShowingFeaturedItemVaultBoyEvent> showingFeaturedItemVaultBoy;  // 190
		ManualCountdownTimer                                displayTimer;                 // 1A8
		ManualCountdownTimer                                postDisplayCooldownTimer;     // 1B4
		ManualCountdownTimer                                syncedEventTimer;             // 1C0
		// NOTE: real field is BSTHeapObjectArena<ExperienceModelData, 32> (confirmed 0x38 bytes via Ghidra --
		// see class comment above). ExperienceModelData itself has no independently-confirmed layout anywhere
		// (not in this fork, not in LucaDotGit), and BSTObjectArena's nested Page class requires a complete
		// element type to instantiate, so it is reserved here as opaque bytes pending a follow-up RE pass.
		std::byte                                        experienceUpdatesA[0x38];        // 1D0
		mutable BSSpinLock                               experienceArenaLock;             // 208
		BSTValueEventSource<ExperienceMeterDisplayEvent> experienceDisplayData;           // 210
		BSTOptional<XPChangeData>                        currentSyncedXP;                 // 230
		ManualCountdownTimer                             experienceDisplayTimer;          // 244
		ManualCountdownTimer                             experienceSoundDelayTimer;       // 250
		ManualCountdownTimer                             experienceDisplayCooldownTimer;  // 25C
		CountdownTimer                                   experienceSoundCooldownTimer;    // 268
	};
	static_assert(sizeof(HUDNotificationsModel) == 0x280);
}
