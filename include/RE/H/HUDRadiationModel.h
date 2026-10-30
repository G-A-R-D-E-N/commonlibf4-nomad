#pragma once

#include "RE/B/BSSoundHandle.h"
#include "RE/B/BSSpinLock.h"
#include "RE/B/BSStringT.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/C/CountdownTimer.h"
#include "RE/C/CurrentRadiationSourceCount.h"
#include "RE/C/CurrentRadsDisplayMagnitude.h"
#include "RE/C/CurrentRadsPercentOfLethal.h"
#include "RE/N/nsUIDebug_UIDebugLogger_NoOp.h"
#include "RE/P/PlayerRadiationDamageData.h"

namespace RE::PlayerActiveEffectChanged
{
	class Event;
}

namespace RE
{
	class EndLoadGameEvent;

	// Ghidra-confirmed (OG 1.10.163, cross-checked AE 1.11.221/1.11.240 via HUDDataModel's own ctor boundary
	// [radiationModel spans HUDDataModel+0x698..+0x910 == 0x278]): the ctor decompiles cleanly with
	// radSoundTierThresholds at +0x38 (BSTSmallArray, verified 0x78-byte footprint = 26 floats, matching
	// BSTSmallArrayHeapAllocator<104>), perFrameRadsDosage at +0xB0, currentPlayerRadsPercent at +0xC8,
	// environmentalRadiationSourceCount at +0xE0, environmentalDamageA at +0xF8 (Ghidra-recovered symbol
	// "BSTArray<PlayerRadiationDamageData,BSTSmallArrayHeapAllocator<128>>" == 16 elements), ingestionDamageA
	// at +0x188, radsSoundTimer at +0x218, radWarningDisplayTimer at +0x230, ingestionRadiationTimer at +0x248,
	// radsSoundHandle at +0x260, currSoundTier at +0x268, matching LucaDotGit's layout exactly through that
	// point. radiationDamageArrayLock's offset is corrected below (see member comment): LucaDotGit's own
	// "+0x27C" comment is mathematically impossible given BSSpinLock's confirmed 8-byte size and the total
	// 0x278 struct size (0x27C + 8 > 0x278); the ctor's own zero-init writes (qword @ +0x268, dword @ +0x270)
	// place the lock at +0x270, which this header uses instead.
	class __declspec(novtable) HUDRadiationModel :
		public BSTEventSink<PlayerActiveEffectChanged::Event>,  // 00
		public BSTEventSink<EndLoadGameEvent>,                  // 08
		public nsUIDebug::UIDebugLogger_NoOp                    // 10
	{
	public:
		inline static constexpr auto RTTI{ RTTI::HUDRadiationModel };
		inline static constexpr auto VTABLE{ VTABLE::HUDRadiationModel };

		~HUDRadiationModel() override;  // 00

		// override (BSTEventSink<PlayerActiveEffectChanged::Event>)
		BSEventNotifyControl ProcessEvent(const PlayerActiveEffectChanged::Event& a_event, BSTEventSource<PlayerActiveEffectChanged::Event>* a_eventSource) override;  // 01

		// override (BSTEventSink<EndLoadGameEvent>)
		BSEventNotifyControl ProcessEvent(const EndLoadGameEvent& a_event, BSTEventSource<EndLoadGameEvent>* a_eventSource) override;  // 01

		// members
		BSStaticStringT<22>                              currentRadiationSoundString;        // 010
		BSTSmallArray<float, 26>                         radSoundTierThresholds;             // 038
		BSTValueEventSource<CurrentRadsDisplayMagnitude> perFrameRadsDosage;                 // 0B0
		BSTValueEventSource<CurrentRadsPercentOfLethal>  currentPlayerRadsPercent;           // 0C8
		BSTValueEventSource<CurrentRadiationSourceCount> environmentalRadiationSourceCount;  // 0E0
		BSTSmallArray<PlayerRadiationDamageData, 16>     environmentalDamageA;               // 0F8
		BSTSmallArray<PlayerRadiationDamageData, 16>     ingestionDamageA;                   // 188
		CountdownTimer                                   radsSoundTimer;                     // 218
		CountdownTimer                                   radWarningDisplayTimer;             // 230
		CountdownTimer                                   ingestionRadiationTimer;            // 248
		BSSoundHandle                                    radsSoundHandle;                    // 260
		std::uint32_t                                    currSoundTier;                      // 268
		mutable BSSpinLock                               radiationDamageArrayLock;           // 270
	};
	static_assert(sizeof(HUDRadiationModel) == 0x278);
}
