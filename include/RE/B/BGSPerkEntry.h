#pragma once

namespace RE
{
	class BGSPerkEntry
	{
	public:
		static constexpr auto RTTI{ RTTI::BGSPerkEntry };
		static constexpr auto VTABLE{ VTABLE::BGSPerkEntry };

		// offset map: docs/RE/evidence/2026-10-30-quest-perk-entry.txt (base extent not yet confirmed)
		void*         vtbl;   // offset 00
		std::uint16_t unk08;  // offset 08
	};
	static_assert(sizeof(BGSPerkEntry) == 0x10);
}
