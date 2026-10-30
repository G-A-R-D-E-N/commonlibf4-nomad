#pragma once

#include "RE/H/hkAabb.h"
#include "RE/H/hknpCompositeShape.h"

namespace RE
{
	class __declspec(novtable) hknpLodShape :
		public hknpCompositeShape
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpLodShape };
		static constexpr auto VTABLE{ VTABLE::hknpLodShape };

		// members
		std::int32_t  numLevelsOfDetail;       // 0x60
		std::byte     infos[0x44];             // 0x64 - 8-element array, internal layout unconfirmed
		void*         shapes[8];               // 0xA8
		std::uint32_t shapesMemorySizes[8];    // 0xE8
		std::int32_t  indexCurrentShapeOnSpu;  // 0x108
		std::byte     pad0x10C[0x4];           // 0x10C
		void*         currentShapePpuAddress;  // 0x110
		std::byte     pad0x118[0x8];           // 0x118
		hkAabb        maximumAabb;             // 0x120
	};
	static_assert(sizeof(hknpLodShape) == 0x140);
}
