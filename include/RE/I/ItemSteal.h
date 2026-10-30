#pragma once

#include "RE/B/BSTEvent.h"

namespace RE
{
	namespace ItemSteal
	{
		class Event
		{
		public:
			// members
			std::uint32_t numStolen;  // 00
		};
		static_assert(sizeof(Event) == 0x4);

		[[nodiscard]] static inline BSTEventSource<ItemSteal::Event>* GetEventSource()
		{
			using func_t = decltype(&ItemSteal::GetEventSource);
			static REL::Relocation<func_t> func{ ID::ItemSteal::GetEventSource };
			return func();
		}
	}
}
