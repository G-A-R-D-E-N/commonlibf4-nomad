#pragma once

#include "RE/B/BSInputEnableLayer.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/P/PlayerInputHandler.h"

namespace RE
{
	class __declspec(novtable) TogglePOVHandler :
		public PlayerInputHandler
	{
	public:
		static constexpr auto RTTI{ RTTI::TogglePOVHandler };
		static constexpr auto VTABLE{ VTABLE::TogglePOVHandler };

		void DebounceTogglePOV()
		{
			povButtonHeld = false;
			nearWorkshop = false;
		}

		// members
		std::uint16_t                                                         unk20;             // 20 - zeroed by the constructor, not read by any code path decompiled
		BSTSmartPointer<BSInputEnableLayer, BSTSmartPointerIntrusiveRefCount> inputEnableLayer;  // 28
		bool                                                                  povButtonHeld;     // 30
		bool                                                                  nearWorkshop;      // 31 - cached workshop-proximity check
	};
	static_assert(sizeof(TogglePOVHandler) == 0x38);
}
