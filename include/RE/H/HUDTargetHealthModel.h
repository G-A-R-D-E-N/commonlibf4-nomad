#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTOptional.h"
#include "RE/C/CountdownTimer.h"
#include "RE/E/EnemyHealthTargetType.h"
#include "RE/H/HUDEnemyHealthDisplayEvent.h"
#include "RE/N/nsUIDebug_UIDebugLogger_NoOp.h"
#include "RE/P/PlayerActivatePickRefEvent.h"
#include "RE/P/PlayerAutoAimActorEvent.h"
#include "RE/V/VATSCommandTargetEvent.h"
#include "RE/V/VATSForcedEnemyHealthPercentEvent.h"

namespace RE
{
	class HUDTargetHealthModel :
		public nsUIDebug::UIDebugLogger_NoOp  // 00
	{
	public:
		// members
		BSTValueEventSink<VATSCommandTargetEvent>            vatsTargetEvent;           // 00
		BSTValueEventSink<PlayerAutoAimActorEvent>           playerAutoAimActor;        // 20
		BSTValueEventSink<PlayerActivatePickRefEvent>        playerActivatePickRef;     // 40
		BSTValueEventSink<VATSForcedEnemyHealthPercentEvent> forcedEnemyHealthPercent;  // 60
		CountdownTimer                                       healthDisplayTimer;        // 80
		BSTOptional<ObjectRefHandle>                         currentHealthTarget;       // 98
		REX::TEnum<EnemyHealthTargetType, std::int32_t>      currentTargetType;         // A0
		BSTValueEventSource<HUDEnemyHealthDisplayEvent>      currentEnemyHealthData;    // A8
	};
	static_assert(sizeof(HUDTargetHealthModel) == 0xD8);
}
