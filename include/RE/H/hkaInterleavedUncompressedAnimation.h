#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkQsTransformf.h"
#include "RE/H/hkaAnimation.h"

namespace RE
{
	class __declspec(novtable) hkaInterleavedUncompressedAnimation :
		public hkaAnimation  // 0x38
	{
	public:
		virtual ~hkaInterleavedUncompressedAnimation();  // 00

		// members
		hkArray<hkQsTransformf> transforms;  // 0x38
		hkArray<float>          floats;      // 0x48
	};
	static_assert(sizeof(hkaInterleavedUncompressedAnimation) == 0x58);
}
