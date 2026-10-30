#pragma once

#include "RE/G/GameMenuBase.h"

namespace RE
{
	class __declspec(novtable) ConsoleNativeUIMenu :
		public GameMenuBase  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::ConsoleNativeUIMenu };
		static constexpr auto VTABLE{ VTABLE::ConsoleNativeUIMenu };
		static constexpr auto MENU_NAME{ "ConsoleNativeUIMenu"sv };

		virtual ~ConsoleNativeUIMenu();  // 00

		// override (GameMenuBase)
		virtual UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;  // 03

		// members
		bool handledInitialEvent{ false };  // E0 - TODO
	};
	static_assert(sizeof(ConsoleNativeUIMenu) == 0xE8);
}
