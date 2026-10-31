#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkaAnimation.h"

namespace RE
{
	struct hkaQuantizedAnimationTrackCompressionParams
	{
		float rotationTolerance;     // 0x00
		float translationTolerance;  // 0x04
		float scaleTolerance;        // 0x08
		float floatingTolerance;     // 0x0C
	};
	static_assert(sizeof(hkaQuantizedAnimationTrackCompressionParams) == 0x10);

	class __declspec(novtable) hkaQuantizedAnimation :
		public hkaAnimation  // 0x40
	{
	public:
		virtual ~hkaQuantizedAnimation();  // 00

		// members
		hkArray<std::uint8_t> data;     // 0x40
		std::uint32_t         endian;   // 0x50
		std::uint32_t         pad54;    // 0x54
		void*                 skeleton; // 0x58
	};
	static_assert(sizeof(hkaQuantizedAnimation) == 0x60);
}
