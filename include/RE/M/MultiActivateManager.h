#pragma once

#include "RE/B/BSStringT.h"

namespace RE
{
	class IMultiActivateUser;

	// ButtonInfo and BUTTON_INDEX decompile-verified on OG 1.10.163 only; the manager's own members are not mapped
	class MultiActivateManager
	{
	public:
		static constexpr auto RTTI{ RTTI::MultiActivateManager };
		static constexpr auto VTABLE{ VTABLE::MultiActivateManager };

		enum class BUTTON_INDEX : std::uint32_t
		{
			kA = 0,
			kB = 1,
			kSecondaryActivate = 1,
			kX = 2,
			kY = 3,
			kCount = 4
		};

		struct ButtonInfo
		{
		public:
			ButtonInfo() = delete;
			ButtonInfo(const ButtonInfo&) = delete;
			ButtonInfo& operator=(const ButtonInfo&) = delete;

			[[nodiscard]] bool IsPopulated() const noexcept { return listener != nullptr; }

			// members
			BSString            label;     // 00
			IMultiActivateUser* listener;  // 10 - BSTSmartPointer in the engine; refcount layout not decompiled, treat as non-owning
			BUTTON_INDEX        index;     // 18 - the default constructor stores kCount
			bool                valid;     // 1C - always set to true by the constructors
		};
		static_assert(sizeof(ButtonInfo) == 0x20);
	};
}
