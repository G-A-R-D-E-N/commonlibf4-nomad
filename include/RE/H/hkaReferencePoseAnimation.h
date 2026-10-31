#pragma once

#include "RE/H/hkaAnimation.h"

namespace RE
{
	class __declspec(novtable) hkaReferencePoseAnimation :
		public hkaAnimation  // 0x38
	{
	public:
		virtual ~hkaReferencePoseAnimation();  // 00
	};
	static_assert(sizeof(hkaReferencePoseAnimation) == 0x40);
}
