#pragma once

#include "RE/H/hkRefPtr.h"
#include "RE/H/hkTransform.h"

namespace RE
{
	class hknpShape;

	class hknpShapeInstance
	{
	public:
		// members
		hkTransformf              transform;       // 0x00
		hkVector4f                scale;           // 0x40
		hkRefPtr<const hknpShape> shape;           // 0x50
		std::uint16_t             shapeTag;        // 0x58
		std::uint16_t             destructionTag;  // 0x5A
		std::uint8_t              padding[30];     // 0x5C
	};
	static_assert(sizeof(hknpShapeInstance) == 0x80);
}
