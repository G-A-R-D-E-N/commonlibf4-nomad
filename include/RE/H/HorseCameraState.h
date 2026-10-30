#pragma once

#include "RE/T/ThirdPersonState.h"

namespace RE
{
	// size and base class from the OG 1.10.163 constructor; members past ThirdPersonState not mapped
	class __declspec(novtable) HorseCameraState :
		public ThirdPersonState
	{
	public:
		static constexpr auto RTTI{ RTTI::HorseCameraState };
		static constexpr auto VTABLE{ VTABLE::HorseCameraState };
		static constexpr auto STATE{ CameraStates::kMount };

		// members
		std::uint64_t unk138;  // 138
		std::uint64_t unk140;  // 140
	};
	static_assert(sizeof(HorseCameraState) == 0x148);
}
