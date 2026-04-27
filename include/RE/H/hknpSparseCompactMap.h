#pragma once

#include "RE/H/hkArray.h"

namespace RE
{
	template <class T>
	class hknpSparseCompactMap
	{
	public:
	private:
		std::uint32_t m_secondaryKeyMask;
		std::uint32_t m_sencondaryKeyBits;
		hkArray<T>    m_primaryKeyToIndex;
		hkArray<T>    m_valueAndSecondaryKeys;
	};
	static_assert(sizeof(hknpSparseCompactMap<std::uint16_t>) == 0x28);
}
