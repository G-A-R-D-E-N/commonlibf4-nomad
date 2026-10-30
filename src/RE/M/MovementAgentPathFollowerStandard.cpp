#include "RE/M/MovementAgentPathFollowerStandard.h"

#include "RE/NativeControllerRuntime.h"

namespace RE
{
	void MovementAgentPathFollowerStandard::PlayActionAtNode(PathFollowerStateUpdateData& a_stateUpdate, std::uint32_t a_nodeIndex)
	{
		if (!detail::IsSupportedNativeControllerRuntime()) {
			return;
		}

		using func_t = decltype(&MovementAgentPathFollowerStandard::PlayActionAtNode);
		static REL::Relocation<func_t> func{ ID::MovementAgentPathFollowerStandard::PlayActionAtNode };
		func(this, a_stateUpdate, a_nodeIndex);
	}
}
