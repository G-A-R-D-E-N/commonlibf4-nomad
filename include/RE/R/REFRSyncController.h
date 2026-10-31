#pragma once

namespace RE
{
	class TESObjectREFR;

	class REFRSyncController
	{
	public:
		REFRSyncController();
		void Add(TESObjectREFR* a_ref, TESObjectREFR* a_target);
		void Update(float a_delta);
	};
}
