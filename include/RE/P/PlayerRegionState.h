#pragma once

#include "RE/B/BSSpinLock.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"

namespace RE
{
	class BGSActorCellEvent;
	class BGSHotloadCompletedEvent;
	class BGSMusicType;
	class TESRegion;
	class TESRegionSound;

	class PlayerRegionState :
		public BSTEventSink<BGSActorCellEvent>,        // 00
		public BSTEventSink<BGSHotloadCompletedEvent>,  // 08
		public BSTSingletonSDM<PlayerRegionState>
	{
	public:
		struct Data
		{
			BSTArray<TESRegionSound*>  regionSounds;                // 00
			BSTArray<TESRegion*>       borderRegions;               // 18
			TESRegion*                 lastKnownWeatherRegion;      // 30
			BGSMusicType*              lastKnownRegionMusic;        // 38
			float                      lastKnownOcclusionAccuracy;  // 40
			float                      lastKnownDistantLODMultiplier;  // 44
			bool                       cellFullyBorderContained;    // 48
			bool                       lastTestInBorderRegion;      // 49
			std::byte                  unk4A[0x06];                 // 4A
			BSReadWriteLock            lock;                        // 50
			void*                      unk58;                       // 58
		};

		static constexpr auto RTTI{ RTTI::PlayerRegionState };

		virtual BSEventNotifyControl ProcessEvent(const BGSActorCellEvent& a_event, BSTEventSource<BGSActorCellEvent>* a_source) override;  // 01
		virtual BSEventNotifyControl ProcessEvent(const BGSHotloadCompletedEvent& a_event, BSTEventSource<BGSHotloadCompletedEvent>* a_source) override;  // 01

		[[nodiscard]] static PlayerRegionState* GetSingleton();

		Data data;  // 18
	};
	static_assert(offsetof(PlayerRegionState, data) == 0x18);
	static_assert(offsetof(PlayerRegionState::Data, regionSounds) == 0x00);
	static_assert(offsetof(PlayerRegionState::Data, borderRegions) == 0x18);
	static_assert(offsetof(PlayerRegionState::Data, lastKnownWeatherRegion) == 0x30);
	static_assert(offsetof(PlayerRegionState::Data, lastKnownRegionMusic) == 0x38);
	static_assert(offsetof(PlayerRegionState::Data, lastKnownOcclusionAccuracy) == 0x40);
	static_assert(offsetof(PlayerRegionState::Data, lastKnownDistantLODMultiplier) == 0x44);
	static_assert(offsetof(PlayerRegionState::Data, cellFullyBorderContained) == 0x48);
	static_assert(offsetof(PlayerRegionState::Data, lastTestInBorderRegion) == 0x49);
	static_assert(offsetof(PlayerRegionState::Data, lock) == 0x50);
	static_assert(offsetof(PlayerRegionState::Data, unk58) == 0x58);
	static_assert(sizeof(PlayerRegionState::Data) == 0x60);
	static_assert(sizeof(PlayerRegionState) == 0x78);
}
