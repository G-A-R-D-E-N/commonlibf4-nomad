#pragma once

#include "RE/H/hkAabb.h"
#include "RE/H/hknpShape.h"

namespace RE
{
	class __declspec(novtable) hknpDummyShape :
		public hknpShape
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpDummyShape };
		static constexpr auto VTABLE{ VTABLE::hknpDummyShape };

		// members
		hkAabb    aabb;           // 0x30
		std::byte signals[0x10];  // 0x50 - hknpShapeSignals
	};
	static_assert(sizeof(hknpDummyShape) == 0x60);
}
