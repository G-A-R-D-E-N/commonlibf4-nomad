#pragma once

#include "RE/N/NiColor.h"
#include "RE/N/NiPointer.h"
#include "RE/S/SkyObject.h"

namespace RE
{
	class BSGeometry;
	class NiTexture;

	class __declspec(novtable) Clouds :
		public SkyObject  // 0x10
	{
	public:
		static constexpr auto RTTI{ RTTI::Clouds };
		static constexpr auto VTABLE{ VTABLE::Clouds };

		enum
		{
			kMaxLayers = 32
		};

		virtual ~Clouds();  // 00

		void Update(Sky* a_sky, float a_delta) override;  // 02

		// members
		NiPointer<BSGeometry> spClouds[kMaxLayers];            // 0x10
		std::uint64_t         hTransTexture[kMaxLayers];       // 0x110
		NiPointer<NiTexture>  spTransTexture[kMaxLayers];      // 0x210
		NiColor               pColors[kMaxLayers];             // 0x310
		float                 fAlpha[kMaxLayers];              // 0x490
		std::uint16_t         usNumLayers;                     // 0x510
		bool                  bForceUpdate;                    // 0x512
	};
	static_assert(sizeof(Clouds) == 0x518);
}
