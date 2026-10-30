#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTTuple.h"
#include "RE/D/DirectionalHitIndicatorResultEvent.h"
#include "RE/H/HUDModes.h"

namespace RE
{
	class HUDModeEvent;
	class TESHitEvent;

	// Ghidra-confirmed (OG 1.10.163, cross-checked AE 1.11.221/1.11.240 via HUDDataModel's own ctor boundary
	// [directionalHitIndicatorDataModel spans HUDDataModel+0x968..+0x9E0 == 0x78]): both ctor and dtor decompile
	// cleanly with currentDirectionalHitIndicators at +0x10, queuedHitSources at +0x40, validHUDModes at +0x58,
	// matching LucaDotGit's layout exactly.
	class __declspec(novtable) HUDDirectionalHitIndicatorDataModel :
		public BSTEventSink<HUDModeEvent>,  // 00
		public BSTEventSink<TESHitEvent>    // 08
	{
	public:
		inline static constexpr auto RTTI{ RTTI::HUDDirectionalHitIndicatorDataModel };
		inline static constexpr auto VTABLE{ VTABLE::HUDDirectionalHitIndicatorDataModel };

		~HUDDirectionalHitIndicatorDataModel() override;  // 00

		// override (BSTEventSink<HUDModeEvent>)
		BSEventNotifyControl ProcessEvent(const HUDModeEvent& a_event, BSTEventSource<HUDModeEvent>* a_eventSource) override;  // 01

		// override (BSTEventSink<TESHitEvent>)
		BSEventNotifyControl ProcessEvent(const TESHitEvent& a_event, BSTEventSource<TESHitEvent>* a_eventSource) override;  // 01

		// members
		BSTValueEventSource<DirectionalHitIndicatorResultEvent> currentDirectionalHitIndicators;  // 10
		BSTArray<BSTTuple<std::uint64_t, ActorHandle>>          queuedHitSources;                 // 40
		HUDModes                                                validHUDModes;                    // 58
	};
	static_assert(sizeof(HUDDirectionalHitIndicatorDataModel) == 0x78);
}
