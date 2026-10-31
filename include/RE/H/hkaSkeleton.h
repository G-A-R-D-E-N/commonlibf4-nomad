#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkQsTransformf.h"
#include "RE/H/hkaBone.h"

namespace RE
{
	class hkaSkeletonPartition
	{
	public:
		const char*  name;        // 0x00
		std::int16_t startBone;   // 0x08
		std::int16_t numBones;    // 0x0A
	};
	static_assert(sizeof(hkaSkeletonPartition) == 0x10);

	class hkaSkeletonLocalFrameOnBone
	{
	public:
		void*        localFrame;  // 0x00
		std::int16_t boneIndex;   // 0x08
	};
	static_assert(sizeof(hkaSkeletonLocalFrameOnBone) == 0x10);

	class __declspec(novtable) hkaSkeleton :
		public hkReferencedObject  // 0x10
	{
	public:
		virtual ~hkaSkeleton();  // 00

		// members
		const char*                          name;             // 0x10
		hkArray<std::int16_t>                parentIndices;    // 0x18
		hkArray<hkaBone>                     bones;            // 0x28
		hkArray<hkQsTransformf>              referencePose;    // 0x38
		hkArray<float>                       referenceFloats;  // 0x48
		hkArray<const char*>                 floatSlots;       // 0x58
		hkArray<hkaSkeletonLocalFrameOnBone> localFrames;      // 0x68
		hkArray<hkaSkeletonPartition>        partitions;       // 0x78
	};
	static_assert(sizeof(hkaSkeleton) == 0x88);
}
