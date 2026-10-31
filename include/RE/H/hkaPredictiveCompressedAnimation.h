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

	class __declspec(novtable) hkaPredictiveCompressedAnimation :
		public hkaAnimation  // 0x40
	{
	public:
		virtual ~hkaPredictiveCompressedAnimation();  // 00

		// members
		hkArray<std::uint8_t>  compressedData;  // 0x40
		hkArray<std::uint16_t> intData;         // 0x50
		std::uint32_t          intArrayOffsets[9];  // 0x60
		std::uint8_t           pad84[4];        // 0x84
		hkArray<float>         floatData;       // 0x88
		std::uint32_t          floatArrayOffsets[3];  // 0x98
		std::int32_t           numBones;        // 0xA4
		std::int32_t           numFloatSlots;   // 0xA8
		std::int32_t           numFrames;       // 0xAC
		std::int32_t           firstFloatBlockScaleAndOffsetIndex;  // 0xB0
		std::uint32_t          padB4;           // 0xB4
		void*                  skeleton;        // 0xB8
		std::int32_t           maxCompressedBytesPerFrame;  // 0xC0
	};
}
