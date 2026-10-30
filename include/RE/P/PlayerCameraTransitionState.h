#pragma once

#include "RE/T/TESCameraState.h"

namespace RE
{
	// size from the OG 1.10.163 constructor allocation; members not mapped
	class __declspec(novtable) PlayerCameraTransitionState :
		public TESCameraState
	{
	public:
		static constexpr auto RTTI{ RTTI::PlayerCameraTransitionState };
		static constexpr auto VTABLE{ VTABLE::PlayerCameraTransitionState };
		static constexpr auto STATE{ CameraStates::kPCTransition };

		// members
		std::byte unk28[0x28];  // 28
	};
	static_assert(sizeof(PlayerCameraTransitionState) == 0x50);
}
