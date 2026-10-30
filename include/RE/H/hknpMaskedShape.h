#pragma once

#include "RE/H/hknpDecoratorShape.h"

namespace RE
{
	class __declspec(novtable) hknpMaskedShape :
		public hknpDecoratorShape
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpMaskedShape };
		static constexpr auto VTABLE{ VTABLE::hknpMaskedShape };

		// members
		void*        mask;                   // 0x40 - pointer, target type unconfirmed
		std::byte    maskWrapper[0x10];      // 0x48 - hknpShapeKeyMask wrapper, internal layout unconfirmed
		std::byte    mutationSignals[0x10];  // 0x58 - hknpShapeSignals
		std::int32_t maskSize;               // 0x68
	};
	static_assert(sizeof(hknpMaskedShape) == 0x70);
}
