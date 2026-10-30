#pragma once

#include "RE/B/BSPointerHandle.h"

namespace RE
{
	// Crosshair/activation pick update emitted by PlayerCharacter and consumed by
	// vanilla rollover/workshop systems. Reverse-engineered layout: the selected
	// reference handle is the first and only observed payload field at +0x00.
	// PrismaHUD previously had to reinterpret the opaque event at this offset.
	struct PickRefUpdateEvent
	{
		ObjectRefHandle pickRef;  // 00
	};
	static_assert(sizeof(PickRefUpdateEvent) == 0x4);
}
