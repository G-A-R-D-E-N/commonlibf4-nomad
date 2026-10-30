#pragma once

#include "RE/G/GameMenuBase.h"

namespace RE
{
	class __declspec(novtable) TutorialMenu :
		public GameMenuBase  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::TutorialMenu };
		static constexpr auto VTABLE{ VTABLE::TutorialMenu };
		static constexpr auto MENU_NAME{ "TutorialMenu"sv };

		virtual ~TutorialMenu();  // 00

		// override (GameMenuBase)
		virtual UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;  // 03
	};
	static_assert(sizeof(TutorialMenu) == 0xE0);
}
