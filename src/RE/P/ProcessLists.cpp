#include "RE/P/ProcessLists.h"

#include "RE/NativeControllerRuntime.h"

namespace RE
{
	void ProcessLists::RunActorUpdates(float a_delta, bool a_onlyPackages)
	{
		if (!detail::IsSupportedNativeControllerRuntime()) {
			return;
		}

		using func_t = decltype(&ProcessLists::RunActorUpdates);
		static REL::Relocation<func_t> func{ ID::ProcessLists::RunActorUpdates };
		func(this, a_delta, a_onlyPackages);
	}
}
