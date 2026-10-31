#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/I/IHandlerFunctor.h"

namespace RE
{
	class Actor;

	class __declspec(novtable) WeaponDrawHandler :
		public IHandlerFunctor<Actor, BSFixedString>
	{
	public:
		static constexpr auto RTTI{ RTTI::WeaponDrawHandler };
		static constexpr auto VTABLE{ VTABLE::WeaponDrawHandler };

		virtual ~WeaponDrawHandler();  // 00

		bool executeHandler(Actor& a_actor, BSFixedString& a_payload) override;  // 01
	};
}
