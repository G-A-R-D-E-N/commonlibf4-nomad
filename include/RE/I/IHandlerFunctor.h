#pragma once

namespace RE
{
	template <class T1, class T2>
	class IHandlerFunctor
	{
	public:
		virtual ~IHandlerFunctor() = default;      // 00
		virtual bool executeHandler(T1& a_target, T2& a_payload) = 0;  // 01
	};
}
