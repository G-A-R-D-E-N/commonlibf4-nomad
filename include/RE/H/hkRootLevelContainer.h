#pragma once

#include "RE/H/hkArray.h"

namespace RE
{
	struct hkNamedVariant
	{
		const char* name;       // 0x00
		const char* className;  // 0x08
		void*       variant;    // 0x10
	};
	static_assert(sizeof(hkNamedVariant) == 0x18);

	class hkRootLevelContainer
	{
	public:
		// members
		hkArray<hkNamedVariant> namedVariants;  // 0x00
	};
	static_assert(sizeof(hkRootLevelContainer) == 0x10);
}
