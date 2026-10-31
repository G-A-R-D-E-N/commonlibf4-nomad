#pragma once

#include "RE/B/BSTEvent.h"

namespace RE
{
	class __declspec(novtable) MountInteraction
	{
	public:
		static constexpr auto RTTI{ RTTI::MountInteraction };
		static constexpr auto VTABLE{ VTABLE::MountInteraction };

		virtual ~MountInteraction();  // 00

		void SyncImpl()
		{
			using func_t = decltype(&MountInteraction::SyncImpl);
			static REL::Relocation<func_t> func{ ID::MountInteraction::SyncImpl };
			func(this);
		}

		void QueuedSync()
		{
			using func_t = decltype(&MountInteraction::QueuedSync);
			static REL::Relocation<func_t> func{ ID::MountInteraction::QueuedSync };
			func(this);
		}
	};
}
