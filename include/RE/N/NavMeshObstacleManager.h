#pragma once

#include "RE/B/BSSpinLock.h"

namespace RE
{
	// Partial population: only the two global relocations below are confirmed.
	// Full member layout (66 named methods per f4-re-mcp) is not yet RE'd -
	// no static_assert(sizeof(...)) or base class until that lands.
	class NavMeshObstacleManager
	{
	public:
		[[nodiscard]] static NavMeshObstacleManager* GetSingleton()
		{
			static REL::Relocation<NavMeshObstacleManager**> singleton{ ID::NavMeshObstacleManager::Singleton };
			return *singleton;
		}

		[[nodiscard]] static BSReadWriteLock& GetUpdateLock()
		{
			static REL::Relocation<BSReadWriteLock*> lock{ ID::NavMeshObstacleManager::UpdateLock };
			return *lock;
		}
	};
}
