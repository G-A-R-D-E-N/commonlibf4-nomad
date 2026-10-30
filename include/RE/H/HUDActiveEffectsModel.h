#pragma once

#include "RE/B/BSSpinLock.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/N/nsUIDebug_UIDebugLogger_NoOp.h"
#include "RE/P/PlayerActiveEffectData.h"
#include "RE/P/PlayerActiveEffectIconsEvent.h"

namespace RE::PlayerActiveEffectChanged
{
	class Event;
}

namespace RE
{
	class EndLoadGameEvent;

	// Ghidra-confirmed (OG 1.10.163, cross-checked AE 1.11.221/1.11.240 via HUDDataModel's own ctor boundary
	// [activeEffectsModel spans HUDDataModel+0xEC0..+0x1320 == 0x460]): both ctor and dtor decompile cleanly
	// with playerActiveEffects (a BSTSmallArray, small-buffer 0x400 bytes / 1024) at +0x10 (not +0x18 as a
	// naive base-class-only reading might suggest -- nsUIDebug::UIDebugLogger_NoOp is empty and collapses with
	// the vtable slots via EBO), playerActiveEffectsLock at +0x420, and CurrentActiveEffectIcons at +0x428,
	// matching LucaDotGit's layout exactly.
	class __declspec(novtable) HUDActiveEffectsModel :
		public BSTEventSink<PlayerActiveEffectChanged::Event>,  // 00
		public BSTEventSink<EndLoadGameEvent>,                  // 08
		public nsUIDebug::UIDebugLogger_NoOp                    // 10
	{
	public:
		inline static constexpr auto RTTI{ RTTI::HUDActiveEffectsModel };
		inline static constexpr auto VTABLE{ VTABLE::HUDActiveEffectsModel };

		~HUDActiveEffectsModel() override;

		// override (BSTEventSink<PlayerActiveEffectChanged::Event>)
		BSEventNotifyControl ProcessEvent(const PlayerActiveEffectChanged::Event& a_event, BSTEventSource<PlayerActiveEffectChanged::Event>* a_eventSource) override;  // 01

		// override (BSTEventSink<EndLoadGameEvent>)
		BSEventNotifyControl ProcessEvent(const EndLoadGameEvent& a_event, BSTEventSource<EndLoadGameEvent>* a_eventSource) override;  // 01

		// members
		BSTSmallArray<PlayerActiveEffectData, 64>         playerActiveEffects;       // 018
		mutable BSSpinLock                                playerActiveEffectsLock;   // 420
		BSTValueEventSource<PlayerActiveEffectIconsEvent> CurrentActiveEffectIcons;  // 428
	};
	static_assert(sizeof(HUDActiveEffectsModel) == 0x460);
}
