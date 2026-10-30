#pragma once

#include "RE/B/BSTEvent.h"

namespace RE
{
	namespace PlayerDifficultySettingChanged
	{
		class Event
		{
		public:
			[[nodiscard]] static BSTEventSource<Event>* GetEventSource()
			{
				using func_t = decltype(&Event::GetEventSource);
				static REL::Relocation<func_t> func{ ID::PlayerDifficultySettingChanged::GetEventSource };
				return func();
			}

			// members
			std::uint32_t oldDifficulty;  // 00
			std::uint32_t newDifficulty;  // 04
		};
		static_assert(sizeof(Event) == 0x8);
	}
}
