#pragma once

#include "RE/M/MultiActivateManager.h"

namespace RE
{
	// slot 03 verified on OG 1.10.163 (MultiActivateManager::OnButtonRelease dispatch); slots 01-02 not decompiled
	class __declspec(novtable) IMultiActivateUser
	{
	public:
		static constexpr auto RTTI{ RTTI::IMultiActivateUser };
		static constexpr auto VTABLE{ VTABLE::IMultiActivateUser };

		virtual ~IMultiActivateUser() = default;  // 00

		// add
		virtual void Unk_01() = 0;                                                     // 01
		virtual void Unk_02() = 0;                                                     // 02
		virtual void OnButtonRelease(MultiActivateManager::BUTTON_INDEX a_index) = 0;  // 03
	};
}
