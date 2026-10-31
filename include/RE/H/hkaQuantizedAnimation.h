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
		public hkaAnimation  // 0x38
	{
	public:
		static constexpr auto RTTI{ RTTI::hkaQuantizedAnimation };

		virtual ~hkaQuantizedAnimation();  // 00

		// members
		hkArray<std::uint8_t> data;      // 0x38
		std::uint32_t         endian;     // 0x48
		void*                 skeleton;   // 0x50
	};
	static_assert(sizeof(hkaQuantizedAnimation) == 0x58);
}
