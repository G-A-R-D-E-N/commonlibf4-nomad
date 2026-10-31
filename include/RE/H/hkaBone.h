#pragma once

namespace RE
{
	class hkaBone
	{
	public:
		const char* name;             // 0x00
		bool        lockTranslation;  // 0x08
	};
	static_assert(sizeof(hkaBone) == 0x10);
}
