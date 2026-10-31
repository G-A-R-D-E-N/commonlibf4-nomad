#pragma once

#include <cstdint>

namespace RE
{
	class __declspec(novtable) BGSPerkEntry
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSPerkEntry };
		static constexpr auto VTABLE{ VTABLE::BGSPerkEntry };

		virtual ~BGSPerkEntry();  // 00

		// members
		std::uint16_t unk08;  // 08
	};
	static_assert(sizeof(BGSPerkEntry) == 0x10);
}
