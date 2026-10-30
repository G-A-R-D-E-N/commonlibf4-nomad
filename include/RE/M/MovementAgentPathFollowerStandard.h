#pragma once

#include "RE/I/IPathFollowerState.h"

namespace RE
{
	class MovementAgentPathFollowerStandard
	{
	public:
		void PlayActionAtNode(PathFollowerStateUpdateData& a_stateUpdate, std::uint32_t a_nodeIndex);
	};
}
