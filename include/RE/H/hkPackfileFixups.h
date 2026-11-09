#pragma once

#include <cstdint>

namespace RE
{
	struct hkPackfileFixup
	{
		std::int32_t from;  // 0x00
		std::int32_t to;    // 0x04
	};
	static_assert(sizeof(hkPackfileFixup) == 0x08);

	struct hkPackfileGlobalFixup
	{
		std::int32_t from;     // 0x00
		std::int32_t section;  // 0x04
		std::int32_t offset;   // 0x08
	};
	static_assert(sizeof(hkPackfileGlobalFixup) == 0x0C);

	struct hkPackfileVirtualFixup
	{
		std::int32_t objectOffset;    // 0x00
		std::int32_t section;         // 0x04
		std::int32_t classNameOffset; // 0x08
	};
	static_assert(sizeof(hkPackfileVirtualFixup) == 0x0C);
}
