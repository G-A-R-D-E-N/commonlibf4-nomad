#pragma once

#include "RE/P/PlayerInputHandler.h"

namespace RE
{
	class __declspec(novtable) RunHandler :
		public PlayerInputHandler
	{
	public:
		static constexpr auto RTTI{ RTTI::RunHandler };
		static constexpr auto VTABLE{ VTABLE::RunHandler };

		// members - PlayerControls::RegisterHandlers allocates this class at a literal 0x30 bytes,
		// confirming each field below sits alone in its own 8-byte slot with no hidden members
		std::uint16_t unk20;         // 20 - zeroed by the constructor, not read by any code path decompiled
		std::byte     padding22[6];  // 22
		bool          isRunning;     // 28
	};
	static_assert(sizeof(RunHandler) == 0x30);
}
