#pragma once

#include "RE/B/BSTMessageQueue.h"

namespace RE
{
	class BSPackedTask
	{
	public:
		std::byte data[0x80];
	};
	static_assert(sizeof(BSPackedTask) == 0x80);

	class BSPackedTaskQueue
	{
	public:
		using UnpackFunc_t = void (*)(const BSPackedTask*);

		bool Process();
		bool QEmpty() const noexcept;
		void Kill();

		// members
		BSTCommonScrapHeapMessageQueue<BSPackedTask> queue;       // 00
		UnpackFunc_t                                 unpackFunc;  // 28
	};
	static_assert(sizeof(BSPackedTaskQueue) == 0x30);
}
