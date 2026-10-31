#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/I/IHandlerFunctor.h"

namespace RE
{
	class Actor;

	class __declspec(novtable) ReadyStateChangeHandler :
		public IHandlerFunctor<Actor, BSFixedString>
	{
	public:
		static constexpr auto RTTI{ RTTI::ReadyStateChangeHandler };
		static constexpr auto VTABLE{ VTABLE::ReadyStateChangeHandler };

		virtual ~ReadyStateChangeHandler();  // 00

		bool executeHandler(Actor& a_actor, BSFixedString& a_payload) override;  // 01
	};
}
