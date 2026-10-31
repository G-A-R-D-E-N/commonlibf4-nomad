#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkaAnimation.h"

namespace RE
{
	class hkaPredictiveCompressedAnimationTrackCompressionParams
	{
	public:
		enum class StorageClass : std::int32_t
		{
			kStatic = 0,
			kDynamic = 1
		};

		StorageClass  storageClass;              // 0x00
		std::uint32_t staticTransformTolerance;  // 0x04
		float         staticFloatTolerance;      // 0x08
	};
	static_assert(sizeof(hkaPredictiveCompressedAnimationTrackCompressionParams) == 0x0C);

	class __declspec(novtable) hkaPredictiveCompressedAnimation :
		public hkaAnimation  // 0x38
	{
	public:
		virtual ~hkaPredictiveCompressedAnimation();  // 00

		// members
		hkArray<std::uint8_t>  compressedData;              // 0x38
		hkArray<std::uint16_t> intData;                     // 0x48
		std::uint32_t          intArrayOffsets[9];          // 0x58
		std::uint8_t           pad7C[4];                    // 0x7C
		hkArray<float>         floatData;                   // 0x80
		std::uint32_t          floatArrayOffsets[3];        // 0x90
		std::int32_t           numBones;                    // 0x9C
		std::int32_t           numFloatSlots;               // 0xA0
		std::int32_t           numFrames;                   // 0xA4
		std::int32_t           firstFloatBlockScaleAndOffsetIndex;  // 0xA8
		std::uint32_t          padAC;                       // 0xAC
		void*                  skeleton;                    // 0xB0
		std::int32_t           maxCompressedBytesPerFrame;  // 0xB8
	};
	static_assert(sizeof(hkaPredictiveCompressedAnimation) == 0xC0);
}
