#pragma once

#include "RE/N/NiPoint3.h"
#include "RE/T/ThirdPersonState.h"

namespace RE
{
	class TESObjectREFR;

	class __declspec(novtable) FurnitureCameraState :
		public ThirdPersonState
	{
	public:
		static constexpr auto RTTI{ RTTI::FurnitureCameraState };
		static constexpr auto VTABLE{ VTABLE::FurnitureCameraState };
		static constexpr auto STATE{ CameraStates::kFurniture };

		void SetFurniture(const TESObjectREFR* a_furniture)
		{
			using func_t = decltype(&FurnitureCameraState::SetFurniture);
			static REL::Relocation<func_t> func{ ID::FurnitureCameraState::SetFurniture };
			return func(this, a_furniture);
		}

		bool QIgnoreFurnitureEnter() const { return ignoreFurnitureEnter; }
		void SetIgnoreFurnitureEnter(bool a_ignore) { ignoreFurnitureEnter = a_ignore; }

		// members
		float    unk138;                // 138 - cached actor heading, refreshed in Begin()
		NiPoint3 offset;                // 13C - furniture-relative camera offset
		float    unk148;                // 148
		float    pitch;                 // 14C - workbench pitch, used directly by GetRotation
		float    headingOffset;         // 150 - added to actor heading by GetRotation
		bool     ignoreFurnitureEnter;  // 154
		bool     isWorkbench;           // 155 - selects the GetRotation code path
		bool     savedAllowAutoVanity;  // 156 - PlayerCamera::allowAutoVanityMode, saved/restored around Begin/End
	};
	static_assert(sizeof(FurnitureCameraState) == 0x158);
}
