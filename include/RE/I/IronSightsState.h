#pragma once

#include "RE/T/TESCameraState.h"

namespace RE
{
	// size from the OG 1.10.163 constructor allocation; members not mapped
	class __declspec(novtable) IronSightsState :
		public TESCameraState
	{
	public:
		static constexpr auto RTTI{ RTTI::IronSightsState };
		static constexpr auto VTABLE{ VTABLE::IronSightsState };
		static constexpr auto STATE{ CameraStates::kIronSights };

		// members
		std::uint64_t unk28;  // 28
	};
	static_assert(sizeof(IronSightsState) == 0x30);
}
