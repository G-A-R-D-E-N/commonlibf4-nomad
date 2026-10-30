#pragma once

#include "RE/H/hkVector4.h"
#include "RE/H/hknpDecoratorShape.h"

namespace RE
{
	class __declspec(novtable) hknpScaledConvexShapeBase :
		public hknpDecoratorShape
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpScaledConvexShapeBase };
		static constexpr auto VTABLE{ VTABLE::hknpScaledConvexShapeBase };

		// members
		hkVector4f scale;        // 0x40
		hkVector4f translation;  // 0x50
	};
	static_assert(sizeof(hknpScaledConvexShapeBase) == 0x60);
}
