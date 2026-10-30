#pragma once

#include "RE/B/BSSpinLock.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTObjectArena.h"
#include "RE/C/CountdownTimer.h"
#include "RE/H/HUDPerkVaultBoySwfDisplayEvent.h"
#include "RE/S/ShowingDialogueSpeechChallengeAnim.h"
#include "RE/S/ShowingPerkVaultBoyState.h"
#include "RE/S/ShowingVATSCritAnim.h"

namespace RE
{
	class HUDPerkVaultBoyData;

	// Ghidra-confirmed (OG 1.10.163, cross-checked AE 1.11.221/1.11.240 via HUDDataModel's own ctor boundary
	// [perkVaultBoyModel spans HUDDataModel+0xB68..+0xC40 == 0xD8]): both ctor and dtor decompile cleanly with
	// displayDataArray at +0x08 (BSTHeapObjectArena, 0x38 bytes), currentPerkVaultBoy at +0x40,
	// hudShowingVaultBoy at +0x70, vatsShowingAnim at +0x88, showingSpeechChallenge at +0xA0,
	// cooldownTimer at +0xB8, matching LucaDotGit's layout exactly.
	class __declspec(novtable) HUDPerkVaultBoyModel :
		public BSTEventSink<HUDPerkVaultBoyData>  // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::HUDPerkVaultBoyModel };
		inline static constexpr auto VTABLE{ VTABLE::HUDPerkVaultBoyModel };

		~HUDPerkVaultBoyModel() override;  // 00

		// override (BSTEventSink<HUDPerkVaultBoyData>)
		BSEventNotifyControl ProcessEvent(const HUDPerkVaultBoyData& a_event, BSTEventSource<HUDPerkVaultBoyData>* a_eventSource) override;  // 01

		// members
		BSTHeapObjectArena<HUDPerkVaultBoyData, 32>           displayDataArray;        // 08
		BSTValueEventSource<HUDPerkVaultBoySwfDisplayEvent>   currentPerkVaultBoy;     // 40
		BSTValueEventSink<ShowingPerkVaultBoyState>           hudShowingVaultBoy;      // 70
		BSTValueEventSink<ShowingVATSCritAnim>                vatsShowingAnim;         // 88
		BSTValueEventSink<ShowingDialogueSpeechChallengeAnim> showingSpeechChallenge;  // A0
		CountdownTimer                                        cooldownTimer;           // B8
		mutable BSSpinLock                                    dataLock;                // D0
	};
	static_assert(sizeof(HUDPerkVaultBoyModel) == 0xD8);
}
