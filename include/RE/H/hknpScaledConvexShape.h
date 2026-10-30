#pragma once

#include "RE/H/hknpScaledConvexShapeBase.h"

namespace RE
{
	class __declspec(novtable) hknpScaledConvexShape :
		public hknpScaledConvexShapeBase
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpScaledConvexShape };
		static constexpr auto VTABLE{ VTABLE::hknpScaledConvexShape };

		// members
		std::byte mutationSignals[0x10];  // 0x60 - hknpShapeSignals
	};
	static_assert(sizeof(hknpScaledConvexShape) == 0x70);
}
