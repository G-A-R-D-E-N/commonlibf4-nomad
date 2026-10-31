#pragma once

#include "RE/N/NiPointer.h"
#include "RE/S/SkyObject.h"

namespace RE
{
	class BSFogProperty;
	class BSTriShape;
	class NiNode;

	class __declspec(novtable) Atmosphere :
		public SkyObject  // 0x10
	{
	public:
		static constexpr auto RTTI{ RTTI::Atmosphere };
		static constexpr auto VTABLE{ VTABLE::Atmosphere };

		virtual ~Atmosphere();  // 00

		void Update(Sky* a_sky, float a_delta) override;  // 02

		// members
		NiPointer<BSTriShape>    spAtmosphere;        // 0x10
		NiPointer<BSFogProperty> spFog;               // 0x18
		NiPointer<NiNode>        spSkyQuadNode;       // 0x20
		NiPointer<BSTriShape>    spSkyQuad;           // 0x28
		bool                     bUpdateFogDistance;  // 0x30
		std::uint8_t             pad31[7];            // 0x31
	};
	static_assert(sizeof(Atmosphere) == 0x38);
}
