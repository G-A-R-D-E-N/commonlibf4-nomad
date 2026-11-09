#pragma once

#include "RE/B/BGSActionData.h"

namespace RE
{
	class __declspec(novtable) TESActionData :
		public BGSActionData  // 0x60
	{
	public:
		static constexpr auto RTTI{ RTTI::TESActionData };
		static constexpr auto VTABLE{ VTABLE::TESActionData };

		virtual ~TESActionData();  // 00

		virtual bool DoIt();  // 05
	};
	static_assert(sizeof(TESActionData) == 0x60);
}
