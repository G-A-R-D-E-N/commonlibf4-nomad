#pragma once

namespace RE
{
	namespace nsStatsMenuUtils
	{
		class ConditionBoyFunctor
		{
		public:
			// members
			std::uint32_t bodyFlags;  // 00
			std::uint32_t headFlags;  // 04
		};
		static_assert(sizeof(ConditionBoyFunctor) == 0x08);

		inline void GetEffectDisplayInfo(MagicItem* a_item, EffectItem* a_effect, float& a_magnitude, float& a_duration)
		{
			using func_t = decltype(&nsStatsMenuUtils::GetEffectDisplayInfo);
			static REL::Relocation<func_t> func{ ID::nsStatsMenuUtils::GetEffectDisplayInfo };
			return func(a_item, a_effect, a_magnitude, a_duration);
		}
	}
}
