#pragma once

#include "RE/H/hkBool.h"
#include "RE/H/hknpClosestHitCollector.h"

namespace RE
{
	class NiAVObject;
	class TESObjectREFR;

	namespace Workshop
	{
		class __declspec(novtable) CheckBuildRadiusCollector :
			public hknpClosestHitCollector  // 0x000
		{
		public:
			static constexpr auto RTTI{ RTTI::Workshop__CheckBuildRadiusCollector };
			static constexpr auto VTABLE{ VTABLE::Workshop__CheckBuildRadiusCollector };  // source:verified vtable ids on all three runtimes

			// override (hknpClosestHitCollector) at offset 0x18
			void AddHit(const hknpCollisionResult& a_hit) override;  // 0x18 [03]

			// members at offset 0x90 and 0x98
			TESObjectREFR* workshopRef;  // 0x90
			NiAVObject*    workshop3D;   // 0x98
		};
		static_assert(sizeof(CheckBuildRadiusCollector) == 0xA0);
	}
}
