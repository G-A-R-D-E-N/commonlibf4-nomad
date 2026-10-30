#pragma once

#include "RE/T/TESCameraState.h"

namespace RE
{
	// size from the OG 1.10.163 constructor allocation; members not mapped
	class __declspec(novtable) TweenMenuCameraState :
		public TESCameraState
	{
	public:
		static constexpr auto RTTI{ RTTI::TweenMenuCameraState };
		static constexpr auto VTABLE{ VTABLE::TweenMenuCameraState };
		static constexpr auto STATE{ CameraStates::kTween };

		// members
		std::byte unk28[0x30];  // 28
	};
	static_assert(sizeof(TweenMenuCameraState) == 0x58);
}
