#pragma once

#include "RE/H/hkbBindable.h"

namespace RE
{
	class hkbNodeInfo;

	class __declspec(novtable) hkbNode :
		public hkbBindable  // 0x30
	{
	public:
		virtual ~hkbNode();  // 00

		// members
		std::uint64_t  userData;    // 0x30
		const char*    name;        // 0x38
		std::uint16_t  id;          // 0x40
		std::int8_t    cloneState;  // 0x42
		std::uint8_t   type;        // 0x43
		std::uint8_t   pad44[4];    // 0x44
		hkbNodeInfo*   nodeInfo;    // 0x48
	};
	static_assert(sizeof(hkbNode) == 0x50);
}
