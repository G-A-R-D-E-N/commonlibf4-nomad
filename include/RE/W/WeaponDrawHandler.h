#pragma once

#include "RE/B/BSFixedString.h"

namespace RE
{
	class Actor;

	class __declspec(novtable) WeaponDrawHandler
	{
	public:
		static constexpr auto RTTI{ RTTI::WeaponDrawHandler };
		static constexpr auto VTABLE{ VTABLE::WeaponDrawHandler };

		virtual ~WeaponDrawHandler();  // 00

		virtual bool executeHandler(Actor& a_actor, BSFixedString& a_payload);  // 01
	};
}
