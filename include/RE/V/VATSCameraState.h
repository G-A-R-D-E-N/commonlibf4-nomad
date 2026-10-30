#pragma once

#include "RE/C/CameraCollisionRig.h"
#include "RE/N/NiPoint3.h"
#include "RE/T/TESCameraState.h"

namespace RE
{
	class NiAVObject;

	class __declspec(novtable) VATSCameraState :
		public TESCameraState
	{
	public:
		static constexpr auto RTTI{ RTTI::VATSCameraState };
		static constexpr auto VTABLE{ VTABLE::VATSCameraState };
		static constexpr auto STATE{ CameraStates::kVATS };

		void SetCameraRotation(float a_x, float a_y, float a_z)
		{
			rotation.x = a_x;
			rotation.y = a_y;
			rotation.z = a_z;
		}

		void SetCameraTranslation(const NiPoint3& a_translation) { translation = a_translation; }

		// members
		CameraCollisionRig collisionRig;      // 28
		NiPoint3           rotation;          // 30
		NiPoint3           translation;       // 3C
		NiAVObject*        targetNode;        // 48 - camera-shot location node, drives collision-rig resets
		float              distance;          // 50 - spring-damped follow distance
		float              distanceVelocity;  // 54
		float              distanceRate;      // 58
	};
	static_assert(sizeof(VATSCameraState) == 0x60);
}
