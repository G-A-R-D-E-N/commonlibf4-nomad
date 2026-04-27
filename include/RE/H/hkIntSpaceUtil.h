#pragma once

#include "RE/H/hkAabb.h"
#include "RE/H/hkVector4.h"

namespace RE
{
	class hkIntSpaceUtil
	{
	public:
		// members
		hkVector4f bitOffsetLow;   // 0x00
		hkVector4f bitOffsetHigh;  // 0x10
		hkVector4f bitScale;       // 0x20
		hkVector4f bitScaleInv;    // 0x30
		hkAabb     aabb;           // 0x40
	};
	static_assert(sizeof(hkIntSpaceUtil) == 0x60);
}
