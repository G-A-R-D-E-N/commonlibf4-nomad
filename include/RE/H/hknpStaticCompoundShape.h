#pragma once

#include "RE/H/hknpCompoundShape.h"

namespace RE
{
	class __declspec(novtable) hknpStaticCompoundShape :
		public hknpCompoundShape
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpStaticCompoundShape };
		static constexpr auto VTABLE{ VTABLE::hknpStaticCompoundShape };

		// members
		void* boundingVolumeData;  // 0xC0 - pointer, target type unconfirmed
	};
	static_assert(sizeof(hknpStaticCompoundShape) == 0xD0);
}
