#pragma once

#include "RE/H/hkaAnimation.h"

namespace RE
{
	class __declspec(novtable) hkaLosslessCompressedAnimation :
		public hkaAnimation  // 0x38
	{
	public:
		virtual ~hkaLosslessCompressedAnimation();  // 00

		// members
		std::uint8_t pad38[0xA8];  // 0x38
	};
	static_assert(sizeof(hkaLosslessCompressedAnimation) == 0xE0);
}
