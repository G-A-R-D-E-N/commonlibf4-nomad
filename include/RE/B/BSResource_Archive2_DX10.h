#pragma once

#include <cstdint>

namespace RE::BSResource::Archive2::DX10
{
	struct Header
	{
		static constexpr std::uint32_t kMagic{ 0x58445442 };  // 'BTDX'
		std::uint8_t data[0x18];  // 0x00 - 24-byte BTDX header
	};
	static_assert(sizeof(Header) == 0x18);

	struct FileEntry
	{
		std::uint8_t data[0x18];  // 0x00 - 24-byte per-file entry
	};
	static_assert(sizeof(FileEntry) == 0x18);

	struct ChunkHeader
	{
		std::uint8_t data[0x18];  // 0x00 - 24-byte per-chunk header
	};
	static_assert(sizeof(ChunkHeader) == 0x18);
}
