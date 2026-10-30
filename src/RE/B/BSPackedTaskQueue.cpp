#include "RE/B/BSPackedTaskQueue.h"

namespace RE
{
	bool BSPackedTaskQueue::Process()
	{
		if (!REX::FModule::IsRuntimeOG()) {
			return false;
		}

		using func_t = bool (*)(BSPackedTaskQueue*);
		static REL::Relocation<func_t> func{ ID::BSPackedTaskQueue::Process };
		return func(this);
	}

	bool BSPackedTaskQueue::QEmpty() const noexcept
	{
		return queue.head == nullptr;
	}

	void BSPackedTaskQueue::Kill()
	{
		if (!REX::FModule::IsRuntimeOG()) {
			return;
		}

		using func_t = void (*)(BSPackedTaskQueue*);
		static REL::Relocation<func_t> func{ ID::BSPackedTaskQueue::Kill };
		return func(this);
	}
}
