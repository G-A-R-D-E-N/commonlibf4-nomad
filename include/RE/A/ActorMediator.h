#pragma once

namespace RE
{
	class __declspec(novtable) ActorMediator
	{
	public:
		static constexpr auto RTTI{ RTTI::ActorMediator };
		static constexpr auto VTABLE{ VTABLE::ActorMediator };

		virtual ~ActorMediator();  // 00
	};
}
