#pragma once

#include "RE/B/BSFixedString.h"

namespace RE
{
	class Actor;

	class __declspec(novtable) BGSActionData
	{
	public:
		BGSActionData() = default;
		virtual ~BGSActionData();  // 00

		// members
		Actor*         actor;        // 0x08
		BSFixedString  unk28;        // 0x28
		BSFixedString  unk30;        // 0x30
		std::int32_t   unk38;        // 0x38
		std::uint8_t   pad3C[4];     // 0x3C
		std::uint8_t   unk40[16];    // 0x40
		std::int32_t   unk50;        // 0x50
		std::uint32_t  pad54;        // 0x54
		std::uint32_t  flags;        // 0x58
		std::uint32_t  pad5C;        // 0x5C
	};
	static_assert(sizeof(BGSActionData) == 0x60);
}
