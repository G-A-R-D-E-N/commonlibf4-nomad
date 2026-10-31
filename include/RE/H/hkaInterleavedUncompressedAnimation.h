#pragma once

#include "RE/H/hkQsTransformf.h"
#include "RE/H/hkaAnimation.h"

namespace RE
{
	class __declspec(novtable) hkaInterleavedUncompressedAnimation :
		public hkaAnimation  // 0x40
	{
	public:
		virtual ~hkaInterleavedUncompressedAnimation();  // 00

		// members
		hkArray<hkQsTransformf> transforms;  // 0x40
		hkArray<float>          floats;      // 0x50
	};
}
