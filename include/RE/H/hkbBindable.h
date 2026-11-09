#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkbVariableBindingSet;
	class hkbBindable;

	class __declspec(novtable) hkbBindable :
		public hkReferencedObject  // 0x10
	{
	public:
		virtual ~hkbBindable();  // 00

		// members
		hkbVariableBindingSet*         variableBindingSet;   // 0x10
		hkArray<hkbBindable*>          cachedBindables;     // 0x18
		bool                           areBindablesCached;  // 0x28
		bool                           hasEnableChanged;   // 0x29
	};
	static_assert(sizeof(hkbBindable) == 0x30);
}
