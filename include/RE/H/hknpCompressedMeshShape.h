#pragma once

#include "RE/H/hknpCompositeShape.h"

namespace RE
{
	class __declspec(novtable) hknpCompressedMeshShape :
		public hknpCompositeShape
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpCompressedMeshShape };
		static constexpr auto VTABLE{ VTABLE::hknpCompressedMeshShape };

		// members
		void*        data;                      // 0x60 - pointer, target type unconfirmed
		std::byte    quadIsFlat[0x18];          // 0x68 - internal layout unconfirmed
		std::byte    triangleIsInterior[0x18];  // 0x80 - internal layout unconfirmed
		std::int32_t numTriangles;              // 0x98
		std::int32_t numConvexShapes;           // 0x9C
	};
	static_assert(sizeof(hknpCompressedMeshShape) == 0xA0);
}
