#pragma once

#include "RE/T/TESCameraState.h"

namespace RE
{
	class __declspec(novtable) AutoVanityState :
		public TESCameraState
	{
	public:
		static constexpr auto RTTI{ RTTI::AutoVanityState };
		static constexpr auto VTABLE{ VTABLE::AutoVanityState };
		static constexpr auto STATE{ CameraStates::kAutoVanity };

		// members
		float rotationAngle;  // 28 - accumulated auto-rotation angle in radians, wraps at 2*PI
	};
	static_assert(sizeof(AutoVanityState) == 0x30);
}
