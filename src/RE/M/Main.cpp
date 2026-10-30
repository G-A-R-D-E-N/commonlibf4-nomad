#include "RE/M/Main.h"

namespace RE
{
	void Main::OnIdle()
	{
		// NG (1.10.984) now has its own id: the prologue at 0xbade20 is byte-identical to the
		// AE 0xc339d0 body, so the call goes through on every runtime.
		using func_t = decltype(&Main::OnIdle);
		static REL::Relocation<func_t> func{ ID::Main::OnIdle };
		return func(this);
	}
}
