#pragma once

#include <cstdint>

namespace RE
{
	struct hkbEventBase
	{
		std::int32_t id;       // 0x00
		std::uint32_t pad04;   // 0x04
		void*        payload;  // 0x08
	};
	static_assert(sizeof(hkbEventBase) == 0x10);

	class hkbEvent :
		public hkbEventBase  // 0x10
	{
	public:
		void* sender;  // 0x10
	};
	static_assert(sizeof(hkbEvent) == 0x18);
}
