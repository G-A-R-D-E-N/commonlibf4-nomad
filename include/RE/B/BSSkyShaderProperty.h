#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSShaderProperty.h"
#include "RE/N/NiColor.h"
#include "RE/N/NiPointer.h"

namespace RE
{
	class BSRenderPass;
	class NiTexture;

	class __declspec(novtable) BSSkyShaderProperty :
		public BSShaderProperty  // 0x70
	{
	public:
		static constexpr auto RTTI{ RTTI::BSSkyShaderProperty };
		static constexpr auto VTABLE{ VTABLE::BSSkyShaderProperty };

		enum class SkyObject : std::int32_t
		{
			kSun = 0,
			kSunGlare = 1,
			kAtmosphere = 2,
			kClouds = 3,
			kSkyQuad = 4,
			kStars = 5,
			kMoon = 6,
			kMoonShadow = 7,
			kOther = 8
		};

		virtual ~BSSkyShaderProperty();  // 00

		// members
		NiColorA             kBlendColor;         // 0x70
		NiPointer<NiTexture> textures[3];         // 0x80
		BSFixedString        textureFilename;     // 0x98
		float                fBlendValue;         // 0xA0
		std::uint16_t        usCloudLayer;        // 0xA4
		bool                 bFadeSecondTexture;  // 0xA6
		std::uint8_t         padA7;               // 0xA7
		SkyObject            skyObjectType;       // 0xA8
		std::uint8_t         padAC[4];            // 0xAC
	};
	static_assert(sizeof(BSSkyShaderProperty) == 0xB0);
}
