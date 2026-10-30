#pragma once

#include "RE/B/BSIntrusiveRefCounted.h"

namespace RE
{
	// vtable address and the three slots are verified on OG/NG/AE; the two virtual names are unverified
	class BSAnimationGraphChannel :
		public BSIntrusiveRefCounted
	{
	public:
		static constexpr auto RTTI{ RTTI::BSAnimationGraphChannel };
		static constexpr auto VTABLE{ VTABLE::BSAnimationGraphChannel };

		virtual ~BSAnimationGraphChannel();  // 00

		virtual void Unk_01() = 0;  // 01
		virtual void Unk_02() = 0;  // 02
	};
}
