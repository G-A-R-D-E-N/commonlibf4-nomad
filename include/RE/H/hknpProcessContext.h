#pragma once

#include "RE/H/hkProcessContext.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hknpDefaultViewerColorScheme.h"

namespace RE
{
	class hknpProcessContextListener;
	class hknpWorld;
	class hkTaskQueue;

	class hknpProcessContext :
		public hkReferencedObject,
		public hkProcessContext
	{
	public:
		hknpProcessContext() = default;

		virtual const char* GetType() override
		{
			return "Physics";
		}

		void AddWorld(hknpWorld* a_world)
		{
			for (auto world : worlds) {
				if (world == a_world)
					return;
			}

			worlds.push_back(a_world);
		}

		void SetColorScheme(hknpViewerColorScheme* a_colorScheme)
		{
			if (a_colorScheme)
				colorScheme = a_colorScheme;
			else
				colorScheme = &defaultColorScheme;
		}

		// members
		hkArray<hknpWorld*>                  worlds;                              // 0xA0
		hkArray<hknpProcessContextListener*> addListeners;                        // 0xB0
		hknpViewerColorScheme*               colorScheme{ &defaultColorScheme };  // 0xC0
		hknpDefaultViewerColorScheme         defaultColorScheme;                  // 0xC8
		hkTaskQueue*                         taskQueue{ nullptr };                // 0xE8
	};
	static_assert(sizeof(hknpProcessContext) == 0xF0);
}
