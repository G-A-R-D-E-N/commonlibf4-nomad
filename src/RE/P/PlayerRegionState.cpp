#include "RE/P/PlayerRegionState.h"

namespace RE
{
	PlayerRegionState* PlayerRegionState::GetSingleton()
	{
		static REL::Relocation<PlayerRegionState**> singleton{ ID::PlayerRegionState::Singleton };
		return *singleton;
	}
}
