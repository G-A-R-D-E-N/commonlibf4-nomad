#include "RE/U/UI.h"

namespace RE
{
	void UI::AdvanceMenus()
	{
		using func_t = decltype(&UI::AdvanceMenus);
		static REL::Relocation<func_t> func{ ID::UI::AdvanceMenus };
		return func(this);
	}

	void UI::CloseAllMenus()
	{
		using func_t = decltype(&UI::CloseAllMenus);
		static REL::Relocation<func_t> func{ ID::UI::CloseAllMenus };
		return func(this);
	}

	void UI::EndRender()
	{
		using func_t = decltype(&UI::EndRender);
		static REL::Relocation<func_t> func{ ID::UI::EndRender };
		return func(this);
	}

	void UI::PreShutdown_ForceCloseAllMenus()
	{
		using func_t = decltype(&UI::PreShutdown_ForceCloseAllMenus);
		static REL::Relocation<func_t> func{ ID::UI::PreShutdown_ForceCloseAllMenus };
		return func(this);
	}

	void UI::ProcessMessages()
	{
		using func_t = decltype(&UI::ProcessMessages);
		static REL::Relocation<func_t> func{ ID::UI::ProcessMessages };
		return func(this);
	}
}
