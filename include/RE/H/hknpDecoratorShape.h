#pragma once

#include "RE/H/hknpShape.h"

namespace RE
{
	class __declspec(novtable) hknpDecoratorShape :
		public hknpShape
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpDecoratorShape };
		static constexpr auto VTABLE{ VTABLE::hknpDecoratorShape };

		// members
		void*        coreShape;      // 0x30 - pointer, target type unconfirmed
		std::int32_t coreShapeSize;  // 0x38
	};
	static_assert(sizeof(hknpDecoratorShape) == 0x40);
}
