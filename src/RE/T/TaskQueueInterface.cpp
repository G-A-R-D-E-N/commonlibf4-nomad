#include "RE/T/TaskQueueInterface.h"

#include "RE/B/BGSMaterialSwap.h"
#include "RE/N/NiAVObject.h"
#include "RE/NativeControllerRuntime.h"

namespace RE
{
	void TaskQueueInterface::QueueApplyMaterialSwap(NiAVObject* a_object, BGSMaterialSwap* a_materialSwap, float a_colorRemappingIndex, bool a_queueForUpdate, bool a_force)
	{
		if (!detail::IsSupportedNativeControllerRuntime()) {
			return;
		}

		using func_t = decltype(&TaskQueueInterface::QueueApplyMaterialSwap);
		static REL::Relocation<func_t> func{ ID::TaskQueueInterface::QueueApplyMaterialSwap };
		func(this, a_object, a_materialSwap, a_colorRemappingIndex, a_queueForUpdate, a_force);
	}

	void TaskQueueInterface::TaskUnpackFunc(const BSPackedTask* a_task)
	{
		if (!detail::IsSupportedNativeControllerRuntime()) {
			return;
		}

		using func_t = void (*)(const BSPackedTask*);
		static REL::Relocation<func_t> func{ ID::TaskQueueInterface::TaskUnpackFunc };
		return func(a_task);
	}
}
