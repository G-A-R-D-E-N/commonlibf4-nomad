#pragma once

namespace RE
{
	// size and the three named offsets observed in hkBinaryPackfileWriter::doDeferredWrites on OG 1.10.163; the writer memsets each header to 0xFF
	struct hkPackfileSectionHeader
	{
	public:
		// members
		std::byte     unk00[0x14];         // 00 - section name is copied into the leading bytes
		std::uint32_t dataStart;           // 14 - absolute offset of the section data
		std::uint32_t unk18;               // 18
		std::uint32_t globalFixupOffset;   // 1C - relative to dataStart; entries are 3 x u32 (src, dstSection, dstOffset)
		std::uint32_t virtualFixupOffset;  // 20 - relative to dataStart; entries are 3 x u32 (src, 0, classNameOffset)
		std::byte     unk24[0x1C];         // 24
	};
	static_assert(sizeof(hkPackfileSectionHeader) == 0x40);
}
