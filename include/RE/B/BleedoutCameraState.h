#pragma once

#include "RE/B/BSSoundHandle.h"
#include "RE/N/NiMatrix3.h"
#include "RE/N/NiPointer.h"
#include "RE/T/ThirdPersonState.h"

namespace RE
{
	class NiAVObject;

	class __declspec(novtable) BleedoutCameraState :
		public ThirdPersonState
	{
	public:
		static constexpr auto RTTI{ RTTI::BleedoutCameraState };
		static constexpr auto VTABLE{ VTABLE::BleedoutCameraState };
		static constexpr auto STATE{ CameraStates::kBleedout };

		// members - NiMatrix3's 16-byte alignment pads 8 bytes before rotationMtx and rounds the
		// class's tail size up to 0x1A0 (a multiple of 16) instead of 0x198
		NiMatrix3             rotationMtx;          // 140
		float                 followDistance;       // 170
		float                 pitch;                // 174
		float                 headingOffset;        // 178 - added to actor heading when trackCameraTarget is set
		float                 randomHeadingOffset;  // 17C - used instead of headingOffset otherwise
		NiPointer<NiAVObject> targetBodyPart3D;     // 180 - cached via GetBodyPart3D, drives GetTargetPos
		BSSoundHandle         soundHandle;          // 188
		bool                  trackCameraTarget;    // 190
	};
	static_assert(sizeof(BleedoutCameraState) == 0x1A0);
}
