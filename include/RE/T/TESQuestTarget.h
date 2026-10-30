#pragma once

#include "RE/B/BSContainer.h"
#include "RE/B/BSTArray.h"
#include "RE/M/MemoryManager.h"
#include "RE/T/TESCondition.h"
#include "REX/TEnumSet.h"

namespace RE
{
	class BGSKeyword;
	class TESObjectREFR;

	// Investigated as part of a quests/Papyrus audit: the only public reference
	// (LucaDotGit_CommonLibF4) models this as a bare, non-polymorphic struct containing only a
	// "flags" member at offset 0x00. Address Library carries an OG-only id (583915) for
	// TESQuestTarget::`scalar deleting destructor', which normally implies a virtual destructor -
	// but that turned out to be a red herring here:
	//   - the ctor (OG rva 0x5fad30) writes a literal 0 (MOV byte ptr [rdi], 0) at offset 0x00,
	//     never an address, so there is no vtable pointer;
	//   - ~TESQuestTarget (OG rva 0x5fad80) never stomps a vtable pointer on entry (standard MSVC
	//     codegen for a genuinely polymorphic class does this, even under LTCG elision the write
	//     is normally still observable via disassembly patterns that aren't present here);
	//   - an exhaustive byte-pattern scan of the entire OG 1.10.163 image (validated against a
	//     known-good vtable, RE::VTABLE::BGSBaseAlias) found zero references anywhere to the
	//     `scalar deleting destructor' address - no vtable slot, no indirect dispatch site;
	//   - there is no RTTI TypeDescriptor for this class either (no ".?AVTESQuestTarget@@" or even
	//     a bare "TESQuestTarget" ASCII string anywhere in the image);
	//   - TESQuestTarget::UpdateTargetArray is called via a fixed, non-virtual CALL from multiple
	//     sites that hold only a `TESQuestTarget*` of unknown concrete type (BGSQuestObjective's
	//     TargetListUpdater functors), which would require indirect vtable dispatch if the method
	//     were actually virtual;
	//   - TESQuest::Load allocates the object directly via `operator new(0x38)` then calls
	//     TESQuestTarget::TESQuestTarget and TESQuestTarget::Load as plain non-virtual calls.
	// Conclusion: TESQuestTarget is NOT polymorphic in this binary (no RE::RTTI/RE::VTABLE ids
	// exist for it). The `scalar deleting destructor' is most likely an MSVC-synthesized
	// destroy-and-deallocate helper kept for exception-unwind cleanup of a partially constructed
	// object (referenced only from SEH/unwind metadata, which is why it has zero ordinary
	// call/data cross-references). LucaDotGit's layout was still wrong, just not for the reason
	// suspected - it captured only 1 of 8 real members (sizeof is 0x38, confirmed via the
	// `operator new(0x38)` call in TESQuest::Load, not the handful of bytes their "flags"-only
	// struct implies).
	//
	// Confirmed (OG 1.10.163) via Ghidra decompilation of the ctor/dtor, Load, InitItem,
	// SetConditions, GetConditions, GetIgnoreLocks, QStraightLinePath, UpdateTargetRef,
	// UpdateTargetArray, GetRefData, IsEmpty, ForEachTargetData<F>. None of these carry an
	// Address Library id (OG or AE), and no AE/NG address could be bridged for them (no
	// map_og_ae entry, and BGSQuestObjective::AddTarget/RemoveTarget/ClearTargetList - the only
	// nearby confirmed OG<->AE anchors - never actually call into TESQuestTarget). Left unwrapped
	// rather than guessing an id; the layout below and the trivial accessors that need no engine
	// call are the only things landed.
	class TESQuestTarget
	{
	public:
		class REF_DATA;  // inherits TeleportPath + tracking data; not RE'd yet, held only by pointer

		enum class FLAG : std::uint8_t
		{
			kNone = 0,
			kIgnoreLocks = 1u << 0,
			// bit 1 (0x2) is read/written by Load() but no accessor references it; meaning unconfirmed
			kStraightLinePath = 1u << 2,
		};

		F4_HEAP_REDEFINE_NEW(TESQuestTarget);

		[[nodiscard]] bool GetIgnoreLocks() const noexcept { return flags.all(FLAG::kIgnoreLocks); }
		[[nodiscard]] bool QStraightLinePath() const noexcept { return flags.all(FLAG::kStraightLinePath); }

		[[nodiscard]] TESCondition*       GetConditions() noexcept { return &conditions; }
		[[nodiscard]] const TESCondition* GetConditions() const noexcept { return &conditions; }

		[[nodiscard]] bool IsEmpty() const noexcept { return refData.size() == 0; }

		[[nodiscard]] const REF_DATA* GetRefData(std::uint32_t a_index) const noexcept
		{
			return a_index < refData.size() ? refData[a_index] : nullptr;
		}

		void ForEachTargetData(std::function<BSContainer::ForEachResult(REF_DATA*)> a_callback) const
		{
			for (auto* data : refData) {
				if (a_callback(data) == BSContainer::ForEachResult::kStop) {
					return;
				}
			}
		}

		// members
		REX::TEnumSet<FLAG, std::uint8_t>          flags;       // 00
		TESCondition                               conditions;  // 08
		std::uint32_t                              aliasID;     // 10
		BGSKeyword*                                keyword;     // 18 (raw form id until InitItem resolves it)
		BSTArray<REF_DATA*, BSTArrayHeapAllocator> refData;     // 20
	};
	static_assert(sizeof(TESQuestTarget) == 0x38);
}
