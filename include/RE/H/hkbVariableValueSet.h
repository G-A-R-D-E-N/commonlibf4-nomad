#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkVector4.h"

namespace RE
{
	class hkRefVariant;

	class hkbVariableValue
	{
	public:
		std::int32_t value;  // 0x00
	};
	static_assert(sizeof(hkbVariableValue) == 0x04);

	class __declspec(novtable) hkbVariableValueSet :
		public hkReferencedObject  // 0x10
	{
	public:
		virtual ~hkbVariableValueSet();  // 00

		// members
		hkArray<hkbVariableValue> wordVariableValues;     // 0x10
		hkArray<hkVector4f>       quadVariableValues;     // 0x20
		hkArray<hkRefVariant>     variantVariableValues;  // 0x30
	};
	static_assert(sizeof(hkbVariableValueSet) == 0x40);
}
