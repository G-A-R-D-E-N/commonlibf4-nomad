#pragma once

namespace RE
{
	// size and fixed fields read off hkPackfileHeader::hkPackfileHeader on OG 1.10.163; the constructor memsets the block to 0xFF first
	struct hkPackfileHeader
	{
	public:
		static constexpr std::uint32_t MAGIC0{ 0x57E0E057 };
		static constexpr std::uint32_t MAGIC1{ 0x10C0C010 };

		// members
		std::uint32_t magic0;       // 00
		std::uint32_t magic1;       // 04
		std::byte     unk08[0x20];  // 08
		std::uint8_t  unk28;        // 28 - zeroed by the constructor
		std::byte     unk29[0xF];   // 29
		std::uint32_t unk38;        // 38 - zeroed by the constructor
		std::uint32_t unk3C;        // 3C
	};
	static_assert(sizeof(hkPackfileHeader) == 0x40);
}
