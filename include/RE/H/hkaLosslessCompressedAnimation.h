#pragma once

#include "RE/H/hkaAnimation.h"

namespace RE
{
	class __declspec(novtable) hkaLosslessCompressedAnimation :
		public hkaAnimation  // 0x40
	{
	public:
		virtual ~hkaLosslessCompressedAnimation();  // 00

		// members
		std::uint8_t pad40[0xA0];  // 0x40
	};
	static_assert(sizeof(hkaLosslessCompressedAnimation) == 0xE0);
}
