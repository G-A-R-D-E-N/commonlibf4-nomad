#pragma once

#include "RE/N/NiPoint3.h"
#include "RE/T/TESCameraState.h"

namespace RE
{
	class NiAVObject;

	class __declspec(novtable) FirstPersonState :
		public TESCameraState
	{
	public:
		static constexpr auto RTTI{ RTTI::FirstPersonState };
		static constexpr auto VTABLE{ VTABLE::FirstPersonState };
		static constexpr auto STATE{ CameraStates::kFirstPerson };

		bool  QCameraOverride() const { return cameraOverride; }
		void  SetCameraOverride(bool a_override) { cameraOverride = a_override; }
		void  SetCameraPitchOverride(bool a_override) { cameraPitchOverride = a_override; }
		float QSittingRotation() const { return sittingRotation; }
		void  SetSittingPitch(float a_pitch) { sittingPitch = a_pitch; }
		void  SetSittingRotation(float a_rotation) { sittingRotation = a_rotation; }

		void GetDampeningOffset(NiPoint3& a_offset) const
		{
			a_offset = dampeningOffset;
		}

		// members
		NiPoint3    lastPosition;            // 28
		NiPoint3    positionDelta;           // 34
		NiPoint3    dampeningOffset;         // 40
		NiAVObject* cameraNode;              // 50 - NiCamera found under the 3D
		NiAVObject* cameraControlNode;       // 58
		float       sittingRotation;         // 60 - yaw offset while sitting
		float       sittingPitch;            // 64 - pitch offset while sitting
		float       pitchOffsetMult;         // 68
		float       lastPitchOffsetMult;     // 6C
		float       pitchOffsetChaseValue;   // 70
		float       pitchOffsetTargetValue;  // 74
		float       ismBlendFactor;          // 78
		float       dampenRampFactor;        // 7C
		bool        cameraOverride;          // 80
		bool        cameraPitchOverride;     // 81
		bool        unk82;                   // 82 - true by default
		bool        unk83;                   // 83
		bool        unk84;                   // 84
	};
	static_assert(sizeof(FirstPersonState) == 0x88);
}
