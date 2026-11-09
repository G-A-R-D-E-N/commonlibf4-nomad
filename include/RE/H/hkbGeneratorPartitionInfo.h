#pragma once

#include <cstdint>

namespace RE
{
	class hkbGeneratorPartitionInfo
	{
	public:
		std::uint32_t boneMask[8];         // 0x00
		std::uint32_t partitionMask;       // 0x20
		std::int16_t  numBones;            // 0x24
		std::int16_t  numMaxPartitions;    // 0x26
	};
	static_assert(sizeof(hkbGeneratorPartitionInfo) == 0x28);
}
