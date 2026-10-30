#pragma once

namespace RE
{
	class CameraCollisionRigImpl;

	// PIMPL wrapper embedded by value in camera states that need collision-adjusted
	// framing (e.g. VATSCameraState).
	class CameraCollisionRig
	{
	public:
		// members
		CameraCollisionRigImpl* impl;  // 00
	};
	static_assert(sizeof(CameraCollisionRig) == 0x8);
}
