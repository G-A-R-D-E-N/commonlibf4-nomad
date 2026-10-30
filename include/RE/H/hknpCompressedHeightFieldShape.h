#pragma once

#include "RE/H/hknpHeightFieldShape.h"

namespace RE
{
	class __declspec(novtable) hknpCompressedHeightFieldShape :
		public hknpHeightFieldShape
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpCompressedHeightFieldShape };
		static constexpr auto VTABLE{ VTABLE::hknpCompressedHeightFieldShape };

		// members
		std::byte storage[0x10];    // 0xF0 - array of uint16, internal layout unconfirmed
		std::byte shapeTags[0x10];  // 0x100 - array of uint16, internal layout unconfirmed
		bool      triangleFlip;     // 0x110
		std::byte pad0x111[0x3];    // 0x111
		float     offset;           // 0x114
		float     scale;            // 0x118
	};
	static_assert(sizeof(hknpCompressedHeightFieldShape) == 0x120);
}
