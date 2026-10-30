#pragma once

#include "RE/B/BSTEvent.h"

namespace RE
{
	class BGSActorCellEvent;
	class BGSHotloadCompletedEvent;

	class PlayerRegionState :
		public BSTEventSink<BGSActorCellEvent>,        // 00
		public BSTEventSink<BGSHotloadCompletedEvent>,  // 08
		public BSTSingletonSDM<PlayerRegionState>
	{
	public:
		static constexpr auto RTTI{ RTTI::PlayerRegionState };

		virtual BSEventNotifyControl ProcessEvent(const BGSActorCellEvent& a_event, BSTEventSource<BGSActorCellEvent>* a_source) override;  // 01
		virtual BSEventNotifyControl ProcessEvent(const BGSHotloadCompletedEvent& a_event, BSTEventSource<BGSHotloadCompletedEvent>* a_source) override;  // 01

		[[nodiscard]] static PlayerRegionState* GetSingleton();
	};
}
