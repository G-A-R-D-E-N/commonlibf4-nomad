#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkaAnimation.h"

namespace RE
{
	class __declspec(novtable) hkaSplineCompressedAnimation :
		public hkaAnimation  // 0x40
	{
	public:
		virtual ~hkaSplineCompressedAnimation();  // 00

		// members
		std::int32_t  numFrames;                // 0x40
		std::int32_t  numBlocks;                // 0x44
		std::int32_t  maxFramesPerBlock;        // 0x48
		std::int32_t  maskAndQuantizationSize;  // 0x4C
		float         blockDuration;            // 0x50
		float         blockInverseDuration;     // 0x54
		float         frameDuration;            // 0x58
		std::uint32_t padding;                  // 0x5C
		hkArray<std::uint32_t> blockOffsets;      // 0x60
		hkArray<std::uint32_t> floatBlockOffsets; // 0x70
		hkArray<std::uint32_t> transformOffsets;  // 0x80
		hkArray<std::uint32_t> floatOffsets;      // 0x90
		hkArray<std::uint8_t>  data;              // 0xA0
		std::uint8_t           endian;            // 0xB0
	};
}
