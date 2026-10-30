#pragma once

#include "RE/C/CombatMathUtilities_Shape.h"

namespace RE::CombatMathUtilities
{
	template <class T>
	class ShapeT :
		public CombatMathUtilities::Shape
	{
	};
	static_assert(sizeof(ShapeT<int>) == 0x04);
}
