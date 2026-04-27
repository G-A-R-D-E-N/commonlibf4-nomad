#pragma once

#include "RE/H/hkAabb16.h"
#include "RE/H/hkHalf.h"
#include "RE/H/hkTransform.h"
#include "RE/H/hknpBodyId.h"
#include "RE/H/hknpBodyQualityId.h"
#include "RE/H/hknpCollisionFlags.h"
#include "RE/H/hknpMaterialId.h"
#include "RE/H/hknpMotionId.h"

namespace RE
{
	class hknpShape;

	class hknpBody
	{
	public:
		enum class SpuFlagsEnum : std::int32_t
		{
			kForceNarrowPhasePPU = 0x1
		};

		// members
		hkTransform                         transform;                                 // 0x00
		hknpCollisionFlags                  flags;                                     // 0x40
		std::uint32_t                       collisionFilterInfo;                       // 0x44
		const hknpShape*                    shape;                                     // 0x48
		hkAabb16                            aabb;                                      // 0x50
		hknpBodyId                          id;                                        // 0x60
		hknpBodyId                          nextAttachedBodyId;                        // 0x64
		hknpMotionId                        motionId;                                  // 0x68
		std::uint32_t                       broadPhaseId;                              // 0x6C
		hknpMaterialId                      materialId;                                // 0x70
		hknpBodyQualityId                   qualityId;                                 // 0x72
		std::uint8_t                        timAngle;                                  // 0x73
		std::uint16_t                       maxTimDistance;                            // 0x74
		std::uint16_t                       maxContactDistance;                        // 0x76
		std::uint32_t                       indexIntoActiveListOrDeactivatedIslandId;  // 0x78
		hkHalf                              radiusOfComCenteredBoundingSphere;         // 0x7C
		hkFlags<SpuFlagsEnum, std::uint8_t> spuFlags;                                  // 0x7E
		std::uint8_t                        shapeSizeDiv16;                            // 0x7F
		std::uint16_t                       motionToBodyRotation[4];                   // 0x80 - hkPackedUnitVector<4>
		std::uint64_t                       userData;                                  // 0x88
	};
	static_assert(sizeof(hknpBody) == 0x90);
}
