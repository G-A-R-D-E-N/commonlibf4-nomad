#pragma once

namespace RE
{
	class hkClass;
	class hkClassEnum;

	// layout decoded from the static member tables on OG 1.10.163 (hkbVariableBounds_Members)
	struct hkClassMember
	{
	public:
		static constexpr std::uint8_t TYPE_STRUCT{ 25 };

		// members
		const char*        name;         // 00
		const hkClass*     memberClass;  // 08
		const hkClassEnum* memberEnum;   // 10
		std::uint8_t       type;         // 18
		std::uint8_t       subtype;      // 19
		std::int16_t       cArraySize;   // 1A
		std::uint16_t      flags;        // 1C
		std::uint16_t      offset;       // 1E
		const void*        attributes;   // 20
	};
	static_assert(sizeof(hkClassMember) == 0x28);
}
