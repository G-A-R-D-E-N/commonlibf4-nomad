#pragma once

namespace RE
{
	class PlayerRegionState
	{
	public:
		static constexpr auto RTTI{ RTTI::PlayerRegionState };

		[[nodiscard]] static PlayerRegionState* GetSingleton();
	};
}
