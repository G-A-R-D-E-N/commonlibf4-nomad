#pragma once

#include "RE/B/BSTEvent.h"
#include "RE/E/ExplosiveIndicatorResultEvent.h"
#include "RE/H/HUDModes.h"

namespace RE
{
	class HUDModeEvent;

	// Ghidra-confirmed (OG 1.10.163, cross-checked AE 1.11.221/1.11.240 via HUDDataModel's own ctor boundary
	// [explosivesDataModel spans HUDDataModel+0x910..+0x968 == 0x58]): HUDExplosivesDataModel::HUDExplosivesDataModel
	// and ~HUDExplosivesDataModel both decompile cleanly with CurrentExplosiveIndicators at +0x08 and
	// ValidHUDModes at +0x38, matching LucaDotGit's layout exactly.
	class __declspec(novtable) HUDExplosivesDataModel :
		public BSTEventSink<HUDModeEvent>  // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::HUDExplosivesDataModel };
		inline static constexpr auto VTABLE{ VTABLE::HUDExplosivesDataModel };

		~HUDExplosivesDataModel() override;  // 00

		// override (BSTEventSink<HUDModeEvent>)
		BSEventNotifyControl ProcessEvent(const HUDModeEvent& a_event, BSTEventSource<HUDModeEvent>* a_eventSource) override;  // 01

		// members
		BSTValueEventSource<ExplosiveIndicatorResultEvent> CurrentExplosiveIndicators;  // 08
		HUDModes                                           ValidHUDModes;               // 38
	};
	static_assert(sizeof(HUDExplosivesDataModel) == 0x58);
}
