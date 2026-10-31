#pragma once

#include <cstdint>

namespace RE
{
	class BSReadWriteLock
	{
	public:
		// members
		std::uint32_t writerThreadID;      // 0x00
		volatile std::uint32_t lockValue;  // 0x04
	};
	static_assert(sizeof(BSReadWriteLock) == 0x08);
}
