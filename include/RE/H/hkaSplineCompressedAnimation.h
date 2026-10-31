#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkaAnimation.h"

namespace RE
{
	class __declspec(novtable) hkaSplineCompressedAnimation :
		public hkaAnimation  // 0x38
	{
	public:
		virtual ~hkaSplineCompressedAnimation();  // 00

		// members
		std::int32_t numFrames;             // 0x38
		std::int32_t numBlocks;             // 0x3C
		std::int32_t maxFramesPerBlock;     // 0x40
		std::int32_t maskAndQuantizationSize;  // 0x44
		float        blockDuration;         // 0x48
		float        blockInverseDuration;  // 0x4C
		float        frameDuration;         // 0x50
		std::uint32_t padding;              // 0x54
		hkArray<std::uint32_t> blockOffsets;       // 0x58
		hkArray<std::uint32_t> floatBlockOffsets;  // 0x68
		hkArray<std::uint32_t> transformOffsets;   // 0x78
		hkArray<std::uint32_t> floatOffsets;       // 0x88
		hkArray<std::uint8_t>  data;               // 0x98
		std::uint8_t           endian;             // 0xA8
	};
	static_assert(sizeof(hkaSplineCompressedAnimation) == 0xB0);
}
