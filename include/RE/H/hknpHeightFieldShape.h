#pragma once

#include "RE/H/hkAabb.h"
#include "RE/H/hkVector4.h"
#include "RE/H/hknpCompositeShape.h"

namespace RE
{
	class __declspec(novtable) hknpHeightFieldShape :
		public hknpCompositeShape
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpHeightFieldShape };
		static constexpr auto VTABLE{ VTABLE::hknpHeightFieldShape };

		// members
		hkAabb       aabb;                          // 0x60
		hkVector4f   floatToIntScale;               // 0x80
		hkVector4f   intToFloatScale;               // 0x90
		std::int32_t intSizeX;                      // 0xA0
		std::int32_t intSizeZ;                      // 0xA4
		std::int32_t numBitsX;                      // 0xA8
		std::int32_t numBitsZ;                      // 0xAC
		std::byte    minMaxTree[0x30];              // 0xB0 - internal layout unconfirmed
		std::int32_t minMaxTreeCoarseness;          // 0xE0
		bool         includeShapeKeyInSdfContacts;  // 0xE4
	};
	static_assert(sizeof(hknpHeightFieldShape) == 0xF0);
}
