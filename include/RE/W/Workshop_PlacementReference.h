#pragma once

#include "RE/N/NEW_REFR_DATA.h"
#include "RE/N/NiPoint3.h"
#include "RE/T/TESBoundObject.h"
#include "RE/T/TESDataHandler.h"
#include "RE/W/Workshop.h"

namespace RE::Workshop
{
	// Workshop::PlacementItemTranslLS - the placement item's local-space translation.
	// Its .y is the hold distance, which InitializePlacementReference falls back to for
	// objects with no XY bounds.
	//
	// Two-argument VariantID, so NG resolves the AE id. Unlike function ids, the NG and
	// AE *data* id spaces are disjoint (nothing in the 479xxxx range appears in the
	// 1.10.984 database), and the NG id could not be recovered because no 1.10.984
	// binary was available to analyse. On NG this therefore fails loudly rather than
	// silently reading the wrong address. Callers who need NG should use the
	// InitializePlacementReference overload that takes the fallback distance directly.
	[[nodiscard]] inline NiPoint3* GetPlacementItemTranslLS()
	{
		static REL::Relocation<NiPoint3*> value{ ID::Workshop::PlacementItemTranslLS };
		return value.get();
	}

	// TESBoundObject::GetBoundXSize - half the diagonal of the object's XY footprint.
	// Reimplemented rather than relocated: the original (OG 0x1403251c0) is 49 bytes of
	// arithmetic over members this library already exposes, so there is nothing to bind.
	// The intermediate truncation back to std::int16_t matches the original, which
	// subtracts as shorts before widening.
	[[nodiscard]] inline float GetBoundXSize(const TESBoundObject& a_object)
	{
		const auto& min = a_object.boundData.boundMin;
		const auto& max = a_object.boundData.boundMax;

		const std::int32_t x = static_cast<std::int16_t>(min.x - max.x);
		const std::int32_t y = static_cast<std::int16_t>(min.y - max.y);

		return std::sqrt(static_cast<float>(x * x + y * y)) * 0.5F;
	}

	// Reimplementation of Workshop::InitializePlacementReference (OG 0x140215050), which
	// the compiler inlined into its only caller (Workshop::CreateNewReference) on NG and
	// AE, leaving no address to bind on those runtimes. The library previously shipped
	// this as REL::VariantID{ 1577199, 0 }, which terminates the game on anything but OG.
	//
	// Spawns the placement reference 1000 units below the point the player is looking at,
	// pushed out along the look direction by a_distance, and stores its handle in
	// Workshop::PlacementItem. The original creates it below the world and lets the
	// placement code lift it into position, which is why the z offset is applied here and
	// not by the caller.
	inline void InitializePlacementReference(const ContextData& a_context, TESBoundObject& a_object, float a_distance)
	{
		NEW_REFR_DATA data;

		data.location = a_context.lookPos + (a_context.lookDir * a_distance);
		data.location.z -= 1000.0F;
		data.direction = NiPoint3{ 0.0F, 0.0F, 0.0F };
		data.object = std::addressof(a_object);
		data.interior = a_context.parentCell;
		data.world = a_context.worldSpace;
		data.clearStillLoadingFlag = true;
		data.initializeScripts = false;

		// data.extra is a BSTSmartPointer, so the release the original does by hand on the
		// way out happens in ~NEW_REFR_DATA here
		*GetPlacementItem() = TESDataHandler::GetSingleton()->CreateReferenceAtLocation(data);
	}

	// Original two-argument signature. Objects with no XY bounds fall back to the current
	// hold distance, which costs a read of PlacementItemTranslLS - see the note on
	// GetPlacementItemTranslLS for why that read is not available on NG.
	inline void InitializePlacementReference(const ContextData& a_context, TESBoundObject& a_object)
	{
		const auto size = GetBoundXSize(a_object);
		InitializePlacementReference(a_context, a_object, size > 0.0F ? size : GetPlacementItemTranslLS()->y);
	}
}
