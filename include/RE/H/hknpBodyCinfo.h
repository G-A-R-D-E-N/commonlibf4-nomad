#pragma once

#include "RE/H/hkQuaternion.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkStringPtr.h"
#include "RE/H/hkVector4.h"
#include "RE/H/hknpBody.h"

namespace RE
{
	class hkLocalFrame;

	class hknpBodyCinfo
	{
	public:
		hknpBodyCinfo()
		{
			using func_t = void (*)(hknpBodyCinfo*);
			static REL::Relocation<func_t> func{ ID::hknpBodyCinfo::ctor };
			func(this);
		}

		// members
		const hknpShape*                              shape;                       // 0x00
		hknpBodyId                                    reservedBodyId;              // 0x08
		hknpMotionId                                  motionId;                    // 0x0C
		hknpBodyQualityId                             qualityId;                   // 0x10
		hknpMaterialId                                materialId;                  // 0x12
		std::uint32_t                                 collisionFilterInfo;         // 0x14
		hknpCollisionFlags                            flags;                       // 0x18
		float                                         collisionLookAheadDistance;  // 0x1C
		hkStringPtr                                   name;                        // 0x20
		std::uint64_t                                 userData;                    // 0x28
		hkVector4f                                    position;                    // 0x30
		hkQuaternionf                                 orientation;                 // 0x40
		hkFlags<hknpBody::SpuFlagsEnum, std::uint8_t> spuFlags;                    // 0x50
		hkRefPtr<hkLocalFrame>                        localFrame;                  // 0x58
	};
	static_assert(sizeof(hknpBodyCinfo) == 0x60);
}
