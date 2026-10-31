#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/I/IHandlerFunctor.h"

namespace RE
{
	class Actor;

	class __declspec(novtable) GunDownStateChangeHandler :
		public IHandlerFunctor<Actor, BSFixedString>
	{
	public:
		static constexpr auto RTTI{ RTTI::GunDownStateChangeHandler };
		static constexpr auto VTABLE{ VTABLE::GunDownStateChangeHandler };

		virtual ~GunDownStateChangeHandler();  // 00

		bool executeHandler(Actor& a_actor, BSFixedString& a_payload) override;  // 01
	};
}
