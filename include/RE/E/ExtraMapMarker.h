#pragma once

#include "RE/B/BSExtraData.h"

namespace RE
{
	class MapMarkerData;

	class __declspec(novtable) ExtraMapMarker :
		public BSExtraData  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::ExtraMapMarker };
		static constexpr auto VTABLE{ VTABLE::ExtraMapMarker };
		static constexpr auto TYPE{ EXTRA_DATA_TYPE::kMapMarker };

		virtual bool CompareImpl(const BSExtraData& a_compare) const override  // 01
		{
			using func_t = decltype(&ExtraMapMarker::CompareImpl);
			static REL::Relocation<func_t> func{ ID::ExtraMapMarker::CompareImpl };
			return func(this, a_compare);
		}

		// members
		MapMarkerData* mapMarkerData;  // 18
	};
	static_assert(sizeof(ExtraMapMarker) == 0x20);
}
