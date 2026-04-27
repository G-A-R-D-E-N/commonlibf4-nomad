#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hknpCollisionQueryCollector.h"
#include "RE/H/hknpCollisionResult.h"

namespace RE
{
	class __declspec(novtable) hknpClosestHitCollector :
		public hknpCollisionQueryCollector  // 0x000
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpClosestHitCollector };
		static constexpr auto VTABLE{ VTABLE::hknpClosestHitCollector };

		// override (hknpCollisionQueryCollector)
		void                       Reset() override;                             // 01
		void                       AddHit(const hknpCollisionResult&) override;  // 02
		bool                       HasHit() const override;                      // 03
		std::int32_t               GetNumHits() const override;                  // 04
		const hknpCollisionResult* GetHits() const override;                     // 05

		// members
		hknpCollisionResult result;  // 0x20
		bool                hasHit;  // 0x80
	};
	static_assert(sizeof(hknpClosestHitCollector) == 0x90);
}
