#pragma once

#include "RE/B/BSTEvent.h"

namespace RE
{
	namespace ItemPickpocketed
	{
		class Event
		{
		public:
			// members
			const Actor* pickerActor;     // 00
			const Actor* victimActor;     // 08
			bool         firstItemTaken;  // 10
		};
		static_assert(sizeof(Event) == 0x18);

		[[nodiscard]] static inline BSTEventSource<ItemPickpocketed::Event>* GetEventSource()
		{
			using func_t = decltype(&ItemPickpocketed::GetEventSource);
			static REL::Relocation<func_t> func{ ID::ItemPickpocketed::GetEventSource };
			return func();
		}
	}
}
