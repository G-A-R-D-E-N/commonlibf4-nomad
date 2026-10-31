#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkVector4.h"
#include "RE/H/hkaAnimatedReferenceFrame.h"

namespace RE
{
	class __declspec(novtable) hkaDefaultAnimatedReferenceFrame :
		public hkaAnimatedReferenceFrame  // 0x10
	{
	public:
		virtual ~hkaDefaultAnimatedReferenceFrame();  // 00

		// members
		std::uint8_t            pad18[0x08];  // 0x18
		hkVector4f              up;       // 0x20
		hkVector4f              forward;  // 0x30
		float                   duration; // 0x40
		std::uint8_t            pad44[4]; // 0x44
		hkArray<hkVector4f>     samples;  // 0x48
	};
	// the inline hkVector4f members force 16-byte alignment, so the class rounds to 0x60
	static_assert(sizeof(hkaDefaultAnimatedReferenceFrame) == 0x60);
}
