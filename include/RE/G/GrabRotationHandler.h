#pragma once

#include "RE/P/PlayerInputHandler.h"

namespace RE
{
	class __declspec(novtable) GrabRotationHandler :
		public PlayerInputHandler
	{
	public:
		static constexpr auto RTTI{ RTTI::GrabRotationHandler };
		static constexpr auto VTABLE{ VTABLE::GrabRotationHandler };

		// members - PlayerControls::RegisterHandlers allocates this class at a literal 0x30 bytes,
		// confirming each field below sits alone in its own 8-byte slot with no hidden members
		std::uint16_t unk20;         // 20 - zeroed by the constructor, not read by any code path decompiled
		std::byte     padding22[6];  // 22
		std::uint8_t  rotationAxis;  // 28 - cycles 0/1/2 each Sprint press, selects the axis passed to PlayerCharacter::ModGrabUserRotation
	};
	static_assert(sizeof(GrabRotationHandler) == 0x30);
}
