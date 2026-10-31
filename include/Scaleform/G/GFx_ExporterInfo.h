#pragma once

#include "Scaleform/F/Flags.h"
#include "Scaleform/G/GFx_FileTypeConstants.h"

namespace Scaleform::GFx
{
	class ExporterInfo
	{
	public:
		enum class ExportFlagConstants : std::uint32_t
		{
			kGlyphTexturesExported = 1 << 0,
			kGradientTexturesExported = 1 << 1,
			kGlyphsStripped = 1 << 4
		};

		// members
		Flags<FileTypeConstants::FileFormatType> format;       // 0x00
		std::uint8_t                             pad04[0x14];  // 0x04
		std::uint16_t                            version;      // 0x18
		Flags<ExportFlagConstants>               exportFlags;  // 0x1C
		const char*                              prefix;       // 0x20
		const char*                              swfName;      // 0x28
		std::uint32_t*                           unk30;        // 0x30
	};
	static_assert(sizeof(ExporterInfo) == 0x38);
}
