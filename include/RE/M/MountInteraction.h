#pragma once

#include "RE/B/BSTEvent.h"

namespace RE
{
	class Actor;

	class __declspec(novtable) MountInteraction
	{
	public:
		static constexpr auto RTTI{ RTTI::MountInteraction };
		static constexpr auto VTABLE{ VTABLE::MountInteraction };

		virtual ~MountInteraction();  // 00

		void SyncImpl();
		void QueuedSync();
		void SyncWithMount(Actor* a_mount);
	};
}
