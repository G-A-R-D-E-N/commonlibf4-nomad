#pragma once

#include "RE/A/Actor.h"
#include "RE/B/BSConnectPoint.h"
#include "RE/B/BSExtraData.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSPointerHandleSmartPointer.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/B/BSTTuple.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiPointer.h"
#include "RE/P/PowerUtils.h"
#include "RE/T/TESObjectCELL.h"

namespace RE
{
	class ActorValueInfo;
	class BGSDefaultObject;
	class bhkNPCollisionObject;
	class hknpShape;
	class hkVector4f;
	class NiTransform;
	class PickRefUpdateEvent;
	class TESBoundObject;

	enum class COL_LAYER;

	namespace Workshop
	{
		// defined elsewhere; only ever named through BSTEventSink<T>*, so a declaration is enough
		class ItemGrabbedEvent;
		class ItemRepairedEvent;
		class ItemScrappedEvent;
		class PowerOffEvent;
		class PowerOnEvent;

		// GetAssignmentCategoryForActor returns byte values that index a 12-entry array of
		// per-category ActorValue pointers (Workshop::ppAssignmentCategoryActorValueFormsA,
		// populated by a C++ dynamic initializer at OG RVA 0x29bc480). Confirmed via decompile
		// of the function and its dispatch lambda, cross-checked OG vs AE (byte-identical
		// structure both runtimes, same 'Q'/0x51 extra-data tag): indices 0/1 come from
		// ActorValue::resourceFood/resourceSafety (see ActorValue.h, offsets 0x358/0x368);
		// indices 2-9 come from named Workshop::WorkshopResource*AVObject globals; index 10 is
		// an explicit null slot the dispatch loop can never select; index 11 is written
		// explicitly by the dispatch lambda whenever no category's ActorValue check passes -
		// the de facto unassigned/idle sentinel. GetAssignmentCategoryForActor also
		// short-circuits to 3 (kScavenger) before ever consulting the array, when a virtual
		// distance-style check on the actor returns positive - actors far from the workshop
		// are treated as scavenging. Names below are inferred from the underlying
		// ActorValue/form each index reads, not extracted from debug symbols.
		//
		// Important precondition: the byte defaults to 0 (kFarmer) before the dispatch
		// lambda ever runs, and stays 0 - indistinguishable from a real kFarmer result -
		// if the actor has no linked ref at all, or the linked ref has no matching
		// extra-data. That path is separate from the explicit kUnassigned (11) write and
		// is only reachable for an actor that isn't a properly-initialized settlement
		// assignee (no workbench/furniture link yet). Callers enumerating a workshop's
		// actual settler actors won't hit it, but treat kFarmer results with suspicion if
		// the actor's assignment state is otherwise unknown.
		enum class AssignmentCategory : std::int8_t
		{
			kFarmer = 0x0,
			kGuard = 0x1,
			kProvisioner = 0x2,
			kScavenger = 0x3,
			kVendorGeneral = 0x4,
			kVendorClinic = 0x5,
			kVendorClothing = 0x6,
			kVendorArmor = 0x7,
			kVendorWeapons = 0x8,
			kVendorBar = 0x9,
			kUnassigned = 0xB
		};

		// GetPlacementRestrictions has exactly these 4 return statements and no others, so the
		// value set is exhaustively confirmed. The 3 non-zero cases are each gated on a
		// different unnamed global reference (no symbol in the Address Library at any of the
		// three addresses), so what specifically kUnk1-kUnk3 represent was not identified.
		enum class PlacementRestrictions : std::uint8_t
		{
			kNone = 0x0,
			kUnk1 = 0x1,
			kUnk2 = 0x2,
			kUnk3 = 0x3
		};

		enum class PlacementStatusValue : std::int8_t
		{
			kNoEditItem = 0x0,
			kValidPlacement = 0x1,
			kFloating = 0x2,
			kIntersecting = 0x3,
			kTerrainOnly = 0x4,
			kWaterRestriction = 0x5,
			kSplineTooLong = 0x6,
			kOutsideBuildArea = 0x7,
			kRedundantSpline = 0x8,
			kAttachedSplineInvalid = 0x9,
			kUnsupported = 0xA,
			kMustSnap = 0xB,
			kRadiusOverlap = 0xC,
			kTimer = 0xD,
			kReasonCount = 0xE
		};

		enum class StartWorkshopStatus
		{
			kOk = 0x0,
			kNoNearbyWorkshop = 0x1,
			kAlreadyInWorkshopMode = 0x2,
			kActivationBlocked = 0x3
		};

		class BuildableAreaEvent
		{
		public:
			// members
			bool exit;  // 00
		};
		static_assert(sizeof(BuildableAreaEvent) == 0x1);

		class ContextData
		{
		public:
			ContextData(Actor* a_actor)
			{
				// lookDir.y = 1.0f;
				zAngle = a_actor->data.angle.z;
				parentCell = a_actor->parentCell;
				worldSpace = a_actor->parentCell->worldSpace;
				a_actor->GetEyeVector(lookPos, lookDir, false);
			}

			// members
			NiPoint3       lookPos;     // 00
			NiPoint3       lookDir;     // 0C
			float          zAngle;      // 18
			TESObjectCELL* parentCell;  // 20
			TESWorldSpace* worldSpace;  // 28
		};
		static_assert(sizeof(ContextData) == 0x30);

		class DeletedItemInfo
		{
		public:
			~DeletedItemInfo() noexcept {}  // NOLINT(modernize-use-equals-default)

			// members
			TESFormID     formID;  // 0
			std::uint32_t count;   // 4
		};
		static_assert(sizeof(DeletedItemInfo) == 0x8);

		class __declspec(novtable) ExtraData :
			public BSExtraData  // 00
		{
		public:
			static constexpr auto RTTI{ RTTI::Workshop__ExtraData };
			static constexpr auto VTABLE{ VTABLE::Workshop__ExtraData };
			static constexpr auto TYPE{ EXTRA_DATA_TYPE::kWorkshop };

			// members
			PowerUtils::PowerGrid*           currentPowerGrid;  // 18
			BSTArray<PowerUtils::PowerGrid*> powerGrid;         // 20
			BSTArray<DeletedItemInfo*>       deletedItems;      // 38
			std::int32_t                     powerRating;       // 50
			bool                             offGridItems;      // 54
		};
		static_assert(sizeof(ExtraData) == 0x58);

		// members - layout cross-verified three independent ways: the member constructor
		// (writing through `this`), the static Workshop::kLastGroundInfo global's dynamic
		// initializer (writing through its own address), and operator=(const GroundInfo&),
		// all three agreeing on every byte from 0x00 through 0x5B. groundZ and the two bool
		// flags are named from how ClampToGround/CorrectZLocation read them; the rest are
		// genuinely unidentified - unk18 in particular is untouched by all five member
		// functions decompiled while reverse-engineering this type, not merely unnamed.
		class GroundInfo
		{
		public:
			// members
			BSTArray<TESObjectREFR*> hitRefs;      // 00 - collected via AddUnique() when a ground/collision cast connects
			std::byte                unk18[0x10];  // 18
			std::byte                unk28[0x8];   // 28
			std::byte                unk30[0x8];   // 30
			float                    groundZ;      // 38 - resolved ground height; -FLT_MAX sentinel means no ground found
			float                    unk3C;        // 3C - -FLT_MAX by default
			float                    unk40;        // 40 - -FLT_MAX by default
			float                    unk44;        // 44 - -FLT_MAX by default
			float                    unk48;        // 48
			float                    unk4C;        // 4C
			float                    unk50;        // 50 - 0x7FFFFFFF by default
			float                    unk54;        // 54 - 0x7FFFFFFF by default
			bool                     hasGround;    // 58 - gates clamping in ClampToGround/CorrectZLocation
			bool                     unk59;        // 59 - second gating flag, true by default
			std::byte                unk5A;        // 5A
			std::byte                unk5B;        // 5B
		};
		static_assert(sizeof(GroundInfo) == 0x60);

		class ItemDestroyedEvent
		{
		public:
			// members
			NiPointer<TESObjectREFR> workshop;         // 00
			NiPointer<TESObjectREFR> objectDestroyed;  // 08
		};
		static_assert(sizeof(ItemDestroyedEvent) == 0x10);

		class ItemMovedEvent
		{
		public:
			// members
			NiPointer<TESObjectREFR> workshop;   // 00
			NiPointer<TESObjectREFR> movedItem;  // 08
		};
		static_assert(sizeof(ItemMovedEvent) == 0x10);

		class ItemPlacedEvent
		{
		public:
			// members
			NiPointer<TESObjectREFR> workshop;    // 00
			NiPointer<TESObjectREFR> placedItem;  // 08
		};
		static_assert(sizeof(ItemPlacedEvent) == 0x10);

		class alignas(0x10) PlacementItemData
		{
		public:
			void Set(TESObjectREFR& a_refr)
			{
				using func_t = decltype(&PlacementItemData::Set);
				static REL::Relocation<func_t> func{ ID::Workshop::PlacementItemData::Set };
				return func(this, a_refr);
			}

			// members
			ObjectRefHandle                 placementItem;             // 00
			BSTArray<hknpShape*>            dropProxy;                 // 08
			BSTArray<bhkNPCollisionObject*> body;                      // 20
			std::byte                       pad38[0x80 - 0x38];        // 38 - TODO
			float                           sinkDepth;                 // 80
			float                           zOffset;                   // 84
			float                           intersectTolerance;        // 88
			float                           snapPointQueryRadius;      // 8C
			float                           forwardCastZRot;           // 90
			float                           xyBoundOverride;           // 94
			float                           xBoundMinOverride;         // 98
			float                           xBoundMaxOverride;         // 9C
			float                           yBoundMinOverride;         // A0
			float                           yBoundMaxOverride;         // A4
			float                           zBoundMinOverride;         // A8
			float                           zBoundMaxOverride;         // AC
			std::uint32_t                   dropProxyIndex;            // B0
			bool                            anythingIsGround;          // B4
			bool                            clampUp;                   // B5
			bool                            forwardCast;               // B6
			bool                            recenter;                  // B7
			bool                            ignoreSimpleIntersection;  // B8
			bool                            allowUnsupportedStacking;  // B9
			bool                            isSet;                     // BA
			bool                            mustSnap;                  // BB
			bool                            stacksWhenSnapped;         // BC
		};
		static_assert(sizeof(PlacementItemData) == 0xC0);

		class PlacementStatusEvent
		{
		public:
			// members
			PlacementStatusValue value;  // 00
		};
		static_assert(sizeof(PlacementStatusEvent) == 0x1);

		class WorkshopMenuNode
		{
		public:
			~WorkshopMenuNode() { Clear(); }

			void Clear()
			{
				filterKeyword = nullptr;
				parent = nullptr;
				recipe = nullptr;
				row = 0;
				column = 0;
				selected = false;
				children.clear();
			}

			bool FindAndSetSelectedNode(std::uint16_t a_row, std::uint32_t a_crc, std::uint16_t& a_outRow)
			{
				using func_t = decltype(&WorkshopMenuNode::FindAndSetSelectedNode);
				static REL::Relocation<func_t> func{ ID::Workshop::WorkshopMenuNode::FindAndSetSelectedNode };
				return func(this, a_row, a_crc, a_outRow);
			}

			F4_HEAP_REDEFINE_NEW(WorkshopMenuNode);

			// members
			BGSKeyword*                                 filterKeyword{ nullptr };                    // 00
			WorkshopMenuNode*                           parent{ nullptr };                           // 08
			BSTArray<std::unique_ptr<WorkshopMenuNode>> children;                                    // 10
			BGSConstructibleObject*                     recipe{ nullptr };                           // 28
			BGSConstructibleObject*                     sourceFormListRecipe{ nullptr };             // 30
			TESForm*                                    form{ nullptr };                             // 38
			std::uint32_t                               uniqueID{ static_cast<std::uint32_t>(-1) };  // 40
			std::uint16_t                               row{ 0 };                                    // 44
			std::uint16_t                               column{ 0 };                                 // 46
			bool                                        selected{ false };                           // 48
		};
		static_assert(sizeof(WorkshopMenuNode) == 0x50);

		class WorkshopModeEvent
		{
		public:
			// members
			NiPointer<TESObjectREFR> workshop;  // 00
			bool                     start;     // 08
		};
		static_assert(sizeof(WorkshopModeEvent) == 0x10);

		// InitializePlacementReference lives in Workshop_PlacementReference.h - it is inlined
		// away on NG and AE, so it is reimplemented rather than relocated

		inline void AddMovingStackedItem(TESObjectREFR& a_refr, const NiPoint3& a_pos, float a_value)
		{
			using func_t = decltype(&Workshop::AddMovingStackedItem);
			static REL::Relocation<func_t> func{ ID::Workshop::AddMovingStackedItem };
			return func(a_refr, a_pos, a_value);
		}

		inline void AddOtherContainers(BSScrapArray<NiPointer<TESObjectREFR>>& a_containers, const BGSLocation* a_location, bool a_flag)
		{
			using func_t = decltype(&Workshop::AddOtherContainers);
			static REL::Relocation<func_t> func{ ID::Workshop::AddOtherContainers };
			return func(a_containers, a_location, a_flag);
		}

		inline void AddStoredItem(TESObjectREFR* a_refr, const TESForm* a_form, std::uint32_t a_count)
		{
			using func_t = decltype(&Workshop::AddStoredItem);
			static REL::Relocation<func_t> func{ ID::Workshop::AddStoredItem };
			return func(a_refr, a_form, a_count);
		}

		[[nodiscard]] inline std::uint32_t AdjustComponentCount(bool a_scale, std::uint32_t a_count)
		{
			using func_t = decltype(&Workshop::AdjustComponentCount);
			static REL::Relocation<func_t> func{ ID::Workshop::AdjustComponentCount };
			return func(a_scale, a_count);
		}

		[[nodiscard]] inline std::uint32_t AdjustScrapComponentCount(TESBoundObject* a_object, const TESForm& a_form, std::uint32_t a_count)
		{
			using func_t = std::uint32_t (*)(TESBoundObject*, const TESForm&, std::uint32_t);  // overloaded, decltype would be ambiguous
			static REL::Relocation<func_t> func{ ID::Workshop::AdjustScrapComponentCountForObject };
			return func(a_object, a_form, a_count);
		}

		[[nodiscard]] inline std::uint32_t AdjustScrapComponentCount(const TESObjectREFR& a_refr, const TESForm& a_form, std::uint32_t a_count)
		{
			using func_t = std::uint32_t (*)(const TESObjectREFR&, const TESForm&, std::uint32_t);  // overloaded, decltype would be ambiguous
			static REL::Relocation<func_t> func{ ID::Workshop::AdjustScrapComponentCount };
			return func(a_refr, a_form, a_count);
		}

		inline void BuildWorkShopMenuNodeTree()
		{
			using func_t = decltype(&Workshop::BuildWorkShopMenuNodeTree);
			static REL::Relocation<func_t> func{ ID::Workshop::BuildWorkShopMenuNodeTree };
			return func();
		}

		inline void CalculatePowerRating(const TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::CalculatePowerRating);
			static REL::Relocation<func_t> func{ ID::Workshop::CalculatePowerRating };
			return func(a_refr);
		}

		inline void CancelActiveEdit(const ContextData& a_context)
		{
			using func_t = decltype(&Workshop::CancelActiveEdit);
			static REL::Relocation<func_t> func{ ID::Workshop::CancelActiveEdit };
			return func(a_context);
		}

		[[nodiscard]] inline bool CanGoDown()
		{
			using func_t = decltype(&Workshop::CanGoDown);
			static REL::Relocation<func_t> func{ ID::Workshop::CanGoDown };
			return func();
		}

		[[nodiscard]] inline bool CanGoLeft()
		{
			using func_t = decltype(&Workshop::CanGoLeft);
			static REL::Relocation<func_t> func{ ID::Workshop::CanGoLeft };
			return func();
		}

		[[nodiscard]] inline bool CanGoRight()
		{
			using func_t = decltype(&Workshop::CanGoRight);
			static REL::Relocation<func_t> func{ ID::Workshop::CanGoRight };
			return func();
		}

		[[nodiscard]] inline bool CanGoUp()
		{
			using func_t = decltype(&Workshop::CanGoUp);
			static REL::Relocation<func_t> func{ ID::Workshop::CanGoUp };
			return func();
		}

		[[nodiscard]] inline bool CanNavigate()
		{
			using func_t = decltype(&Workshop::CanNavigate);
			static REL::Relocation<func_t> func{ ID::Workshop::CanNavigate };
			return func();
		}

		[[nodiscard]] inline bool CanPlaceItem()
		{
			using func_t = decltype(&Workshop::CanPlaceItem);
			static REL::Relocation<func_t> func{ ID::Workshop::CanPlaceItem };
			return func();
		}

		[[nodiscard]] inline bool CanProduce(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::CanProduce);
			static REL::Relocation<func_t> func{ ID::Workshop::CanProduce };
			return func(a_refr);
		}

		[[nodiscard]] inline bool CanStoreRef(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::CanStoreRef);
			static REL::Relocation<func_t> func{ ID::Workshop::CanStoreRef };
			return func(a_refr);
		}

		[[nodiscard]] inline bool CastSelection(
			const ContextData&                                            a_context,
			const PlacementItemData&                                      a_itemData,
			GroundInfo&                                                   a_groundInfo,
			const hkVector4f&                                             a_castVector,
			NiPoint3&                                                     a_pos,
			NiPoint3&                                                     a_pos2,
			BSTObjectArena<TESObjectREFR*, BSTObjectArenaScrapAlloc, 32>& a_refrs,
			BSTObjectArena<hknpBodyId, BSTObjectArenaScrapAlloc, 32>&     a_bodyIds)
		{
			using func_t = decltype(&Workshop::CastSelection);
			static REL::Relocation<func_t> func{ ID::Workshop::CastSelection };
			return func(a_context, a_itemData, a_groundInfo, a_castVector, a_pos, a_pos2, a_refrs, a_bodyIds);
		}

		inline void CenterPlacementItem(const ContextData& a_context, NiPoint3& a_pos, float& a_value, float a_value2)
		{
			using func_t = decltype(&Workshop::CenterPlacementItem);
			static REL::Relocation<func_t> func{ ID::Workshop::CenterPlacementItem };
			return func(a_context, a_pos, a_value, a_value2);
		}

		[[nodiscard]] inline bool ChangeFocusedRowSelection(bool a_flag, const ContextData& a_context)
		{
			using func_t = decltype(&Workshop::ChangeFocusedRowSelection);
			static REL::Relocation<func_t> func{ ID::Workshop::ChangeFocusedRowSelection };
			return func(a_flag, a_context);
		}

		inline void CheckBed(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::CheckBed);
			static REL::Relocation<func_t> func{ ID::Workshop::CheckBed };
			return func(a_refr);
		}

		[[nodiscard]] inline bool CheckBuildRadius(TESObjectREFR& a_refr, const NiPoint3& a_point)
		{
			using func_t = decltype(&Workshop::CheckBuildRadius);
			static REL::Relocation<func_t> func{ ID::Workshop::CheckBuildRadius };
			return func(a_refr, a_point);
		}

		inline void CheckPlayerPosition(TESObjectREFR* a_refr)
		{
			using func_t = decltype(&Workshop::CheckPlayerPosition);
			static REL::Relocation<func_t> func{ ID::Workshop::CheckPlayerPosition };
			return func(a_refr);
		}

		inline void CheckPowerConnection(ExtraData& a_extraData, TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::CheckPowerConnection);
			static REL::Relocation<func_t> func{ ID::Workshop::CheckPowerConnection };
			return func(a_extraData, a_refr);
		}

		inline void CheckSnappedPowerConnections(const ContextData& a_context, TESObjectREFR& a_refr, const PlacementItemData& a_itemData)
		{
			using func_t = decltype(&Workshop::CheckSnappedPowerConnections);
			static REL::Relocation<func_t> func{ ID::Workshop::CheckSnappedPowerConnections };
			return func(a_context, a_refr, a_itemData);
		}

		[[nodiscard]] inline bool CheckSplineIntersections(const ContextData& a_context, TESObjectREFR& a_refr, TESObjectREFR* a_refr2, TESObjectREFR* a_refr3)
		{
			using func_t = decltype(&Workshop::CheckSplineIntersections);
			static REL::Relocation<func_t> func{ ID::Workshop::CheckSplineIntersections };
			return func(a_context, a_refr, a_refr2, a_refr3);
		}

		[[nodiscard]] inline bool CheckStackItem(TESObjectREFR& a_refr, BSPointerHandle<TESObjectREFR, BSUntypedPointerHandle<21, 5>>& a_handle, bool a_flag)
		{
			using func_t = decltype(&Workshop::CheckStackItem);
			static REL::Relocation<func_t> func{ ID::Workshop::CheckStackItem };
			return func(a_refr, a_handle, a_flag);
		}

		[[nodiscard]] inline bool CheckWire(BGSConstructibleObject* a_recipe)
		{
			using func_t = decltype(&Workshop::CheckWire);
			static REL::Relocation<func_t> func{ ID::Workshop::CheckWire };
			return func(a_recipe);
		}

		inline void ClearItemRecipeMaps()
		{
			using func_t = decltype(&Workshop::ClearItemRecipeMaps);
			static REL::Relocation<func_t> func{ ID::Workshop::ClearItemRecipeMaps };
			return func();
		}

		inline void ClearMovingStackedItems()
		{
			using func_t = decltype(&Workshop::ClearMovingStackedItems);
			static REL::Relocation<func_t> func{ ID::Workshop::ClearMovingStackedItems };
			return func();
		}

		inline void ClearSnappedPowerConnections(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::ClearSnappedPowerConnections);
			static REL::Relocation<func_t> func{ ID::Workshop::ClearSnappedPowerConnections };
			return func(a_refr);
		}

		inline void CollectLinkedWorkshopContainers(BSScrapArray<NiPointer<TESObjectREFR>>& a_containers, bool a_flag)
		{
			using func_t = decltype(&Workshop::CollectLinkedWorkshopContainers);
			static REL::Relocation<func_t> func{ ID::Workshop::CollectLinkedWorkshopContainers };
			return func(a_containers, a_flag);
		}

		inline void CollectScrapRewards(const TESObjectREFR& a_refr, BSScrapArray<BSTTuple<TESBoundObject*, std::uint32_t>>& a_bSScrapArray)
		{
			using func_t = decltype(&Workshop::CollectScrapRewards);
			static REL::Relocation<func_t> func{ ID::Workshop::CollectScrapRewards };
			return func(a_refr, a_bSScrapArray);
		}

		inline void CommitMovingStackedItems(const ContextData& a_context, TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::CommitMovingStackedItems);
			static REL::Relocation<func_t> func{ ID::Workshop::CommitMovingStackedItems };
			return func(a_context, a_refr);
		}

		inline void CopyLinkedContainerContents(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::CopyLinkedContainerContents);
			static REL::Relocation<func_t> func{ ID::Workshop::CopyLinkedContainerContents };
			return func(a_refr);
		}

		inline void CreateNewReference(const ContextData& a_context, bool a_flag)
		{
			using func_t = decltype(&Workshop::CreateNewReference);
			static REL::Relocation<func_t> func{ ID::Workshop::CreateNewReference };
			return func(a_context, a_flag);
		}

		inline void CreateSharedWorkshopContainer(const TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::CreateSharedWorkshopContainer);
			static REL::Relocation<func_t> func{ ID::Workshop::CreateSharedWorkshopContainer };
			return func(a_refr);
		}

		inline void DeleteWorkshopItem(TESObjectREFR* a_refr)
		{
			using func_t = decltype(&Workshop::DeleteWorkshopItem);
			static REL::Relocation<func_t> func{ ID::Workshop::DeleteWorkshopItem };
			return func(a_refr);
		}

		inline void DestroyCurrentItem(const ContextData& a_context, bool a_flag)
		{
			using func_t = decltype(&Workshop::DestroyCurrentItem);
			static REL::Relocation<func_t> func{ ID::Workshop::DestroyCurrentItem };
			return func(a_context, a_flag);
		}

		inline void DestroyItem(const ContextData& a_context, BSPointerHandleSmartPointer<BSPointerHandleManagerInterface<TESObjectREFR, HandleManager>>& a_handle, bool a_flag, bool a_flag2, bool a_flag3)
		{
			using func_t = decltype(&Workshop::DestroyItem);
			static REL::Relocation<func_t> func{ ID::Workshop::DestroyItem };
			return func(a_context, a_handle, a_flag, a_flag2, a_flag3);
		}

		inline void DestroySharedWorkshopContainer()
		{
			using func_t = decltype(&Workshop::DestroySharedWorkshopContainer);
			static REL::Relocation<func_t> func{ ID::Workshop::DestroySharedWorkshopContainer };
			return func();
		}

		inline void DropUnsupportedItems(const ContextData& a_context)
		{
			using func_t = decltype(&Workshop::DropUnsupportedItems);
			static REL::Relocation<func_t> func{ ID::Workshop::DropUnsupportedItems };
			return func(a_context);
		}

		inline void ExpandActiveEdit()
		{
			using func_t = decltype(&Workshop::ExpandActiveEdit);
			static REL::Relocation<func_t> func{ ID::Workshop::ExpandActiveEdit };
			return func();
		}

		[[nodiscard]] inline bool ExportPowerGrid(TESObjectREFR& a_refr, const char* a_ch)
		{
			using func_t = decltype(&Workshop::ExportPowerGrid);
			static REL::Relocation<func_t> func{ ID::Workshop::ExportPowerGrid };
			return func(a_refr, a_ch);
		}

		inline void FindAndRemoveHolotapeFromTerminal(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::FindAndRemoveHolotapeFromTerminal);
			static REL::Relocation<func_t> func{ ID::Workshop::FindAndRemoveHolotapeFromTerminal };
			return func(a_refr);
		}

		[[nodiscard]] inline const BGSLocation* FindLocation()
		{
			using func_t = decltype(&Workshop::FindLocation);
			static REL::Relocation<func_t> func{ ID::Workshop::FindLocation };
			return func();
		}

		[[nodiscard]] inline TESObjectREFR* FindMagRefr(TESObjectREFR& a_refr, const NiPoint3& a_pos, const NiPoint3& a_pos2, const ContextData& a_context)
		{
			using func_t = decltype(&Workshop::FindMagRefr);
			static REL::Relocation<func_t> func{ ID::Workshop::FindMagRefr };
			return func(a_refr, a_pos, a_pos2, a_context);
		}

		[[nodiscard]] inline TESObjectREFR* FindNearbyWorkshop(StartWorkshopStatus& a_status)
		{
			using func_t = decltype(&Workshop::FindNearbyWorkshop);
			static REL::Relocation<func_t> func{ ID::Workshop::FindNearbyWorkshop };
			return func(a_status);
		}

		[[nodiscard]] inline TESObjectREFR* FindNearestValidWorkshop(const TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::FindNearestValidWorkshop);
			static REL::Relocation<func_t> func{ ID::Workshop::FindNearestValidWorkshop };
			return func(a_refr);
		}

		inline void FinishDestroyItem(const ContextData& a_context, BSPointerHandleSmartPointer<BSPointerHandleManagerInterface<TESObjectREFR, HandleManager>>& a_handle, bool a_flag)
		{
			using func_t = decltype(&Workshop::FinishDestroyItem);
			static REL::Relocation<func_t> func{ ID::Workshop::FinishDestroyItem };
			return func(a_context, a_handle, a_flag);
		}

		inline void ForceCloseWorkshop()
		{
			using func_t = decltype(&Workshop::ForceCloseWorkshop);
			static REL::Relocation<func_t> func{ ID::Workshop::ForceCloseWorkshop };
			return func();
		}

		[[nodiscard]] inline bool FreeBuild()
		{
			using func_t = decltype(&Workshop::FreeBuild);
			static REL::Relocation<func_t> func{ ID::Workshop::FreeBuild };
			return func();
		}

		[[nodiscard]] inline Actor* GetAshpileActor(TESObjectREFR* a_refr)
		{
			using func_t = decltype(&Workshop::GetAshpileActor);
			static REL::Relocation<func_t> func{ ID::Workshop::GetAshpileActor };
			return func(a_refr);
		}

		[[nodiscard]] inline bool GetAvailableCount(std::uint32_t& a_count, std::uint32_t a_count2, std::uint32_t a_count3)
		{
			using func_t = decltype(&Workshop::GetAvailableCount);
			static REL::Relocation<func_t> func{ ID::Workshop::GetAvailableCount };
			return func(a_count, a_count2, a_count3);
		}

		// Deliberately TESObjectREFR&, not Actor&: the mangled name and the disassembly
		// agree the compiled function takes TESObjectREFR&, and the vtable call inside it
		// dispatches through ActorValueOwner (a TESObjectREFR base, offset 0x58 - see
		// TESObjectREFR.h) rather than anything Actor-specific, so this genuinely isn't
		// narrowed to Actor at the ABI level.
		[[nodiscard]] inline AssignmentCategory GetAssignmentCategoryForActor(const TESObjectREFR& a_actor)
		{
			using func_t = decltype(&Workshop::GetAssignmentCategoryForActor);
			static REL::Relocation<func_t> func{ ID::Workshop::GetAssignmentCategoryForActor };
			return func(a_actor);
		}

		[[nodiscard]] inline std::uint32_t GetBeds(const TESObjectREFR& a_workshop)
		{
			using func_t = decltype(&Workshop::GetBeds);
			static REL::Relocation<func_t> func{ ID::Workshop::GetBeds };
			return func(a_workshop);
		}

		[[nodiscard]] inline std::int32_t GetBedsRating(const TESObjectREFR& a_workshop)
		{
			using func_t = decltype(&Workshop::GetBedsRating);
			static REL::Relocation<func_t> func{ ID::Workshop::GetBedsRating };
			return func(a_workshop);
		}

		[[nodiscard]] inline float GetBudgetFraction()
		{
			using func_t = decltype(&Workshop::GetBudgetFraction);
			static REL::Relocation<func_t> func{ ID::Workshop::GetBudgetFraction };
			return func();
		}

		[[nodiscard]] inline std::uint32_t GetBuildCount(const WorkshopMenuNode& a_node, std::uint32_t& a_count)
		{
			using func_t = decltype(&Workshop::GetBuildCount);
			static REL::Relocation<func_t> func{ ID::Workshop::GetBuildCount };
			return func(a_node, a_count);
		}

		[[nodiscard]] inline std::uint32_t GetDefaultWaterMaterialID()
		{
			using func_t = decltype(&Workshop::GetDefaultWaterMaterialID);
			static REL::Relocation<func_t> func{ ID::Workshop::GetDefaultWaterMaterialID };
			return func();
		}

		inline void GetEmbeddedNavmesh(TESObjectREFR* a_refr, BSTSmartPointer<NavMesh, BSTSmartPointerIntrusiveRefCount>& a_ptr)
		{
			using func_t = decltype(&Workshop::GetEmbeddedNavmesh);
			static REL::Relocation<func_t> func{ ID::Workshop::GetEmbeddedNavmesh };
			return func(a_refr, a_ptr);
		}

		[[nodiscard]] inline std::uint32_t GetFood(const TESObjectREFR& a_workshop)
		{
			using func_t = decltype(&Workshop::GetFood);
			static REL::Relocation<func_t> func{ ID::Workshop::GetFood };
			return func(a_workshop);
		}

		[[nodiscard]] inline std::int32_t GetFoodRating(const TESObjectREFR& a_workshop)
		{
			using func_t = decltype(&Workshop::GetFoodRating);
			static REL::Relocation<func_t> func{ ID::Workshop::GetFoodRating };
			return func(a_workshop);
		}

		[[nodiscard]] inline std::uint32_t GetGeneratedPower(const TESObjectREFR& a_workshop)
		{
			using func_t = decltype(&Workshop::GetGeneratedPower);
			static REL::Relocation<func_t> func{ ID::Workshop::GetGeneratedPower };
			return func(a_workshop);
		}

		inline void GetGroundInfo(
			GroundInfo&              a_groundInfo,
			const PlacementItemData& a_itemData,
			TESObjectREFR*           a_refr,
			const NiTransform&       a_transform,
			const TESObjectREFR*     a_ignoreRefr,
			bool                     a_flag)
		{
			using func_t = decltype(&Workshop::GetGroundInfo);
			static REL::Relocation<func_t> func{ ID::Workshop::GetGroundInfo };
			return func(a_groundInfo, a_itemData, a_refr, a_transform, a_ignoreRefr, a_flag);
		}

		[[nodiscard]] inline std::uint32_t GetHappiness(const TESObjectREFR& a_workshop)
		{
			using func_t = decltype(&Workshop::GetHappiness);
			static REL::Relocation<func_t> func{ ID::Workshop::GetHappiness };
			return func(a_workshop);
		}

		[[nodiscard]] inline std::int32_t GetHappinessRating(const TESObjectREFR& a_workshop)
		{
			using func_t = decltype(&Workshop::GetHappinessRating);
			static REL::Relocation<func_t> func{ ID::Workshop::GetHappinessRating };
			return func(a_workshop);
		}

		[[nodiscard]] inline std::uint32_t GetHappinessRatingTarget(const TESObjectREFR& a_workshop)
		{
			using func_t = decltype(&Workshop::GetHappinessRatingTarget);
			static REL::Relocation<func_t> func{ ID::Workshop::GetHappinessRatingTarget };
			return func(a_workshop);
		}

		[[nodiscard]] inline std::int32_t GetHappinessTarget(const TESObjectREFR& a_workshop)
		{
			using func_t = decltype(&Workshop::GetHappinessTarget);
			static REL::Relocation<func_t> func{ ID::Workshop::GetHappinessTarget };
			return func(a_workshop);
		}

		[[nodiscard]] inline bool GetIsWireArt(BGSArtObject* a_art)
		{
			using func_t = decltype(&Workshop::GetIsWireArt);
			static REL::Relocation<func_t> func{ ID::Workshop::GetIsWireArt };
			return func(a_art);
		}

		inline void GetLoadedCounts(std::uint32_t& a_loadedCount, std::uint32_t& a_totalCount)
		{
			using func_t = decltype(&Workshop::GetLoadedCounts);
			static REL::Relocation<func_t> func{ ID::Workshop::GetLoadedCounts };
			return func(a_loadedCount, a_totalCount);
		}

		[[nodiscard]] inline ObjectRefHandle GetMapMarkerFromWorkshop(const TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::GetMapMarkerFromWorkshop);
			static REL::Relocation<func_t> func{ ID::Workshop::GetMapMarkerFromWorkshop };
			return func(a_refr);
		}

		[[nodiscard]] inline bool GetNavcutCollisionLayer(COL_LAYER& a_layer)
		{
			using func_t = decltype(&Workshop::GetNavcutCollisionLayer);
			static REL::Relocation<func_t> func{ ID::Workshop::GetNavcutCollisionLayer };
			return func(a_layer);
		}

		[[nodiscard]] inline std::uint8_t GetNavmeshLayer(TESObjectREFR* const a_tESObjectREFRconst)
		{
			using func_t = decltype(&Workshop::GetNavmeshLayer);
			static REL::Relocation<func_t> func{ ID::Workshop::GetNavmeshLayer };
			return func(a_tESObjectREFRconst);
		}

		[[nodiscard]] inline std::uint32_t GetObjectCount(const TESForm& a_object)
		{
			using func_t = decltype(&Workshop::GetObjectCount);
			static REL::Relocation<func_t> func{ ID::Workshop::GetObjectCount };
			return func(a_object);
		}

		inline bool GetPathTextToWorkshopMenuNode(char* a_buffer, const char* a_separator)
		{
			using func_t = decltype(&Workshop::GetPathTextToWorkshopMenuNode);
			static REL::Relocation<func_t> func{ ID::Workshop::GetPathTextToWorkshopMenuNode };
			return func(a_buffer, a_separator);
		}

		[[nodiscard]] inline PlacementRestrictions GetPlacementRestrictions(const TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::GetPlacementRestrictions);
			static REL::Relocation<func_t> func{ ID::Workshop::GetPlacementRestrictions };
			return func(a_refr);
		}

		[[nodiscard]] inline bool GetPlayerInPlayableArea()
		{
			using func_t = decltype(&Workshop::GetPlayerInPlayableArea);
			static REL::Relocation<func_t> func{ ID::Workshop::GetPlayerInPlayableArea };
			return func();
		}

		[[nodiscard]] inline std::uint32_t GetPopulation(const TESObjectREFR& a_workshop)
		{
			using func_t = decltype(&Workshop::GetPopulation);
			static REL::Relocation<func_t> func{ ID::Workshop::GetPopulation };
			return func(a_workshop);
		}

		[[nodiscard]] inline std::int32_t GetPowerRating(const TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::GetPowerRating);
			static REL::Relocation<func_t> func{ ID::Workshop::GetPowerRating };
			return func(a_refr);
		}

		[[nodiscard]] inline BGSConstructibleObject* GetRecipe(const TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::GetRecipe);
			static REL::Relocation<func_t> func{ ID::Workshop::GetRecipe };
			return func(a_refr);
		}

		[[nodiscard]] inline const char* GetRecipeDisplayName(const BGSConstructibleObject& a_recipe)
		{
			using func_t = decltype(&Workshop::GetRecipeDisplayName);
			static REL::Relocation<func_t> func{ ID::Workshop::GetRecipeDisplayName };
			return func(a_recipe);
		}

		[[nodiscard]] inline float GetRestrictedBuildRadius(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::GetRestrictedBuildRadius);
			static REL::Relocation<func_t> func{ ID::Workshop::GetRestrictedBuildRadius };
			return func(a_refr);
		}

		[[nodiscard]] inline std::uint32_t GetSafety(const TESObjectREFR& a_workshop)
		{
			using func_t = decltype(&Workshop::GetSafety);
			static REL::Relocation<func_t> func{ ID::Workshop::GetSafety };
			return func(a_workshop);
		}

		[[nodiscard]] inline std::int32_t GetSafetyRating(const TESObjectREFR& a_workshop)
		{
			using func_t = decltype(&Workshop::GetSafetyRating);
			static REL::Relocation<func_t> func{ ID::Workshop::GetSafetyRating };
			return func(a_workshop);
		}

		[[nodiscard]] inline bool GetSelectedItemHasVariants()
		{
			using func_t = decltype(&Workshop::GetSelectedItemHasVariants);
			static REL::Relocation<func_t> func{ ID::Workshop::GetSelectedItemHasVariants };
			return func();
		}

		[[nodiscard]] inline bool GetSelectedNodeInRowHasChildren(std::uint32_t a_count)
		{
			using func_t = decltype(&Workshop::GetSelectedNodeInRowHasChildren);
			static REL::Relocation<func_t> func{ ID::Workshop::GetSelectedNodeInRowHasChildren };
			return func(a_count);
		}

		[[nodiscard]] inline WorkshopMenuNode* GetSelectedWorkshopMenuNode(std::uint32_t a_row, std::uint32_t& a_column)
		{
			using func_t = decltype(&Workshop::GetSelectedWorkshopMenuNode);
			static REL::Relocation<func_t> func{ ID::Workshop::GetSelectedWorkshopMenuNode };
			return func(a_row, a_column);
		}

		[[nodiscard]] inline std::uint32_t GetStoredItemCount(const TESForm& a_form)
		{
			using func_t = decltype(&Workshop::GetStoredItemCount);
			static REL::Relocation<func_t> func{ ID::Workshop::GetStoredItemCount };
			return func(a_form);
		}

		[[nodiscard]] inline std::uint32_t GetWater(const TESObjectREFR& a_workshop)
		{
			using func_t = decltype(&Workshop::GetWater);
			static REL::Relocation<func_t> func{ ID::Workshop::GetWater };
			return func(a_workshop);
		}

		[[nodiscard]] inline std::int32_t GetWaterRating(const TESObjectREFR& a_workshop)
		{
			using func_t = decltype(&Workshop::GetWaterRating);
			static REL::Relocation<func_t> func{ ID::Workshop::GetWaterRating };
			return func(a_workshop);
		}

		[[nodiscard]] inline TESObjectREFR* GetWorkshop(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::GetWorkshop);
			static REL::Relocation<func_t> func{ ID::Workshop::GetWorkshop };
			return func(a_refr);
		}

		inline void GetWorkshopContainer(TESObjectREFR& a_refr, NiPointer<TESObjectREFR>& a_out)
		{
			using func_t = decltype(&Workshop::GetWorkshopContainer);
			static REL::Relocation<func_t> func{ ID::Workshop::GetWorkshopContainer };
			return func(a_refr, a_out);
		}

		[[nodiscard]] inline BGSKeyword* GetWorkshopLinkedRefKeyword()
		{
			using func_t = decltype(&Workshop::GetWorkshopLinkedRefKeyword);
			static REL::Relocation<func_t> func{ ID::Workshop::GetWorkshopLinkedRefKeyword };
			return func();
		}

		[[nodiscard]] inline std::uint32_t GetWorkshopMenuNodeOriginFileIndex(const WorkshopMenuNode& a_node)
		{
			using func_t = decltype(&Workshop::GetWorkshopMenuNodeOriginFileIndex);
			static REL::Relocation<func_t> func{ ID::Workshop::GetWorkshopMenuNodeOriginFileIndex };
			return func(a_node);
		}

		[[nodiscard]] inline ObjectRefHandle GetWorkshopPickRef()
		{
			using func_t = decltype(&Workshop::GetWorkshopPickRef);
			static REL::Relocation<func_t> func{ ID::Workshop::GetWorkshopPickRef };
			return func();
		}

		[[nodiscard]] inline float GetWorkshopResourceDamage(TESObjectREFR& a_refr, const ActorValueInfo& a_actorValue)
		{
			using func_t = decltype(&Workshop::GetWorkshopResourceDamage);
			static REL::Relocation<func_t> func{ ID::Workshop::GetWorkshopResourceDamage };
			return func(a_refr, a_actorValue);
		}

		inline void HandleLoad3DForSpline(TESObjectREFR& a_refr, NiAVObject* a_node)
		{
			using func_t = decltype(&Workshop::HandleLoad3DForSpline);
			static REL::Relocation<func_t> func{ ID::Workshop::HandleLoad3DForSpline };
			return func(a_refr, a_node);
		}

		inline void HandleReferenceDestructionEvent(TESObjectREFR& a_refr, TESObjectREFR& a_refr2, bool a_flag, bool a_flag2)
		{
			using func_t = decltype(&Workshop::HandleReferenceDestructionEvent);
			static REL::Relocation<func_t> func{ ID::Workshop::HandleReferenceDestructionEvent };
			return func(a_refr, a_refr2, a_flag, a_flag2);
		}

		inline void HandleReferenceEvent(TESObjectREFR& a_refr, TESObjectREFR& a_refr2, bool a_flag)
		{
			using func_t = decltype(&Workshop::HandleReferenceEvent);
			static REL::Relocation<func_t> func{ ID::Workshop::HandleReferenceEvent };
			return func(a_refr, a_refr2, a_flag);
		}

		inline void HandleTurretLifeStateChange(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::HandleTurretLifeStateChange);
			static REL::Relocation<func_t> func{ ID::Workshop::HandleTurretLifeStateChange };
			return func(a_refr);
		}

		inline void HandleUnsupportedItem(const ContextData& a_context, TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::HandleUnsupportedItem);
			static REL::Relocation<func_t> func{ ID::Workshop::HandleUnsupportedItem };
			return func(a_context, a_refr);
		}

		[[nodiscard]] inline bool HasActiveEditItem()
		{
			using func_t = decltype(&Workshop::HasActiveEditItem);
			static REL::Relocation<func_t> func{ ID::Workshop::HasActiveEditItem };
			return func();
		}

		[[nodiscard]] inline bool HasPlacementItem()
		{
			using func_t = decltype(&Workshop::HasPlacementItem);
			static REL::Relocation<func_t> func{ ID::Workshop::HasPlacementItem };
			return func();
		}

		[[nodiscard]] inline bool HasRecipe(const TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::HasRecipe);
			static REL::Relocation<func_t> func{ ID::Workshop::HasRecipe };
			return func(a_refr);
		}

		[[nodiscard]] inline bool HaveSharedPowerGrid(TESObjectREFR& a_refr1, TESObjectREFR& a_refr2)
		{
			using func_t = decltype(&Workshop::HaveSharedPowerGrid);
			static REL::Relocation<func_t> func{ ID::Workshop::HaveSharedPowerGrid };
			return func(a_refr1, a_refr2);
		}

		inline void HighlightAssignedReferences(Actor& a_actor)
		{
			using func_t = decltype(&Workshop::HighlightAssignedReferences);
			static REL::Relocation<func_t> func{ ID::Workshop::HighlightAssignedReferences };
			return func(a_actor);
		}

		inline void HighlightPowerConnections(TESObjectCELL* a_cell)
		{
			using func_t = decltype(&Workshop::HighlightPowerConnections);
			static REL::Relocation<func_t> func{ ID::Workshop::HighlightPowerConnections };
			return func(a_cell);
		}

		inline void InitAssignmentCategoryActorValuePointers()
		{
			using func_t = decltype(&Workshop::InitAssignmentCategoryActorValuePointers);
			static REL::Relocation<func_t> func{ ID::Workshop::InitAssignmentCategoryActorValuePointers };
			return func();
		}

		inline void InitItemRecipeMaps()
		{
			using func_t = decltype(&Workshop::InitItemRecipeMaps);
			static REL::Relocation<func_t> func{ ID::Workshop::InitItemRecipeMaps };
			return func();
		}

		inline void InitSDM()
		{
			using func_t = decltype(&Workshop::InitSDM);
			static REL::Relocation<func_t> func{ ID::Workshop::InitSDM };
			return func();
		}

		inline void InitWorkshopItem(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::InitWorkshopItem);
			static REL::Relocation<func_t> func{ ID::Workshop::InitWorkshopItem };
			return func(a_refr);
		}

		[[nodiscard]] inline bool IsActiveEditItem(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::IsActiveEditItem);
			static REL::Relocation<func_t> func{ ID::Workshop::IsActiveEditItem };
			return func(a_refr);
		}

		[[nodiscard]] inline bool IsDamagedTurret(const TESObjectREFR* a_refr)
		{
			using func_t = decltype(&Workshop::IsDamagedTurret);
			static REL::Relocation<func_t> func{ ID::Workshop::IsDamagedTurret };
			return func(a_refr);
		}

		[[nodiscard]] inline bool IsDeadActor(const TESObjectREFR* a_refr)
		{
			using func_t = decltype(&Workshop::IsDeadActor);
			static REL::Relocation<func_t> func{ ID::Workshop::IsDeadActor };
			return func(a_refr);
		}

		[[nodiscard]] inline bool IsDirectlyStackedOn(TESObjectREFR& a_refr, const TESObjectREFR& a_refr2)
		{
			using func_t = decltype(&Workshop::IsDirectlyStackedOn);
			static REL::Relocation<func_t> func{ ID::Workshop::IsDirectlyStackedOn };
			return func(a_refr, a_refr2);
		}

		[[nodiscard]] inline bool IsInteractionBlocked(const TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::IsInteractionBlocked);
			static REL::Relocation<func_t> func{ ID::Workshop::IsInteractionBlocked };
			return func(a_refr);
		}

		[[nodiscard]] inline bool IsInventoryItem(const TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::IsInventoryItem);
			static REL::Relocation<func_t> func{ ID::Workshop::IsInventoryItem };
			return func(a_refr);
		}

		[[nodiscard]] inline bool IsLocationValid(const TESObjectREFR* a_refr)
		{
			using func_t = decltype(&Workshop::IsLocationValid);
			static REL::Relocation<func_t> func{ ID::Workshop::IsLocationValid };
			return func(a_refr);
		}

		[[nodiscard]] inline bool IsLocationWithinBuildableArea(const TESObjectREFR& a_workshop, const NiPoint3& a_location)
		{
			using func_t = decltype(&Workshop::IsLocationWithinBuildableArea);
			static REL::Relocation<func_t> func{ ID::Workshop::IsLocationWithinBuildableArea };
			return func(a_workshop, a_location);
		}

		[[nodiscard]] inline bool IsMannequin(const TESObjectREFR* a_refr)
		{
			using func_t = decltype(&Workshop::IsMannequin);
			static REL::Relocation<func_t> func{ ID::Workshop::IsMannequin };
			return func(a_refr);
		}

		[[nodiscard]] inline bool IsMatchingMaterial(std::uint32_t a_materialID, const BGSDefaultObject& a_object)
		{
			using func_t = decltype(&Workshop::IsMatchingMaterial);
			static REL::Relocation<func_t> func{ ID::Workshop::IsMatchingMaterial };
			return func(a_materialID, a_object);
		}

		[[nodiscard]] inline bool IsMovingItem(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::IsMovingItem);
			static REL::Relocation<func_t> func{ ID::Workshop::IsMovingItem };
			return func(a_refr);
		}

		[[nodiscard]] inline bool IsMovingStackedItem(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::IsMovingStackedItem);
			static REL::Relocation<func_t> func{ ID::Workshop::IsMovingStackedItem };
			return func(a_refr);
		}

		[[nodiscard]] inline bool IsNewWorkshopItem(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::IsNewWorkshopItem);
			static REL::Relocation<func_t> func{ ID::Workshop::IsNewWorkshopItem };
			return func(a_refr);
		}

		[[nodiscard]] inline bool IsOnPowerGrid(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::IsOnPowerGrid);
			static REL::Relocation<func_t> func{ ID::Workshop::IsOnPowerGrid };
			return func(a_refr);
		}

		[[nodiscard]] inline bool IsPlacementItem(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::IsPlacementItem);
			static REL::Relocation<func_t> func{ ID::Workshop::IsPlacementItem };
			return func(a_refr);
		}

		[[nodiscard]] inline bool IsPlacementItemWire()
		{
			using func_t = decltype(&Workshop::IsPlacementItemWire);
			static REL::Relocation<func_t> func{ ID::Workshop::IsPlacementItemWire };
			return func();
		}

		[[nodiscard]] inline bool IsPowered(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::IsPowered);
			static REL::Relocation<func_t> func{ ID::Workshop::IsPowered };
			return func(a_refr);
		}

		[[nodiscard]] inline bool IsRecalculateResourcesProcessing(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::IsRecalculateResourcesProcessing);
			static REL::Relocation<func_t> func{ ID::Workshop::IsRecalculateResourcesProcessing };
			return func(a_refr);
		}

		[[nodiscard]] inline bool IsRecalculateResourcesQueued(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::IsRecalculateResourcesQueued);
			static REL::Relocation<func_t> func{ ID::Workshop::IsRecalculateResourcesQueued };
			return func(a_refr);
		}

		[[nodiscard]] inline bool IsReferenceWithinBuildableArea(const TESObjectREFR& a_refr1, const TESObjectREFR& a_refr2)
		{
			using func_t = decltype(&Workshop::IsReferenceWithinBuildableArea);
			static REL::Relocation<func_t> func{ ID::Workshop::IsReferenceWithinBuildableArea };
			return func(a_refr1, a_refr2);
		}

		[[nodiscard]] inline bool IsResourceObject(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::IsResourceObject);
			static REL::Relocation<func_t> func{ ID::Workshop::IsResourceObject };
			return func(a_refr);
		}

		[[nodiscard]] inline bool IsScrappingBlocked(const TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::IsScrappingBlocked);
			static REL::Relocation<func_t> func{ ID::Workshop::IsScrappingBlocked };
			return func(a_refr);
		}

		[[nodiscard]] inline bool IsSelectedWorkshopItem(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::IsSelectedWorkshopItem);
			static REL::Relocation<func_t> func{ ID::Workshop::IsSelectedWorkshopItem };
			return func(a_refr);
		}

		[[nodiscard]] inline bool IsSplineValid(const TESObjectREFR* a_refr)
		{
			using func_t = decltype(&Workshop::IsSplineValid);
			static REL::Relocation<func_t> func{ ID::Workshop::IsSplineValid };
			return func(a_refr);
		}

		[[nodiscard]] inline bool IsStacked(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::IsStacked);
			static REL::Relocation<func_t> func{ ID::Workshop::IsStacked };
			return func(a_refr);
		}

		// Returns a_refr as an Actor* if it's an immobile turret actor, nullptr otherwise.
		[[nodiscard]] inline Actor* IsTurret(TESObjectREFR* a_refr)
		{
			using func_t = Actor* (*)(TESObjectREFR*);
			static REL::Relocation<func_t> func{ ID::Workshop::IsTurret };
			return func(a_refr);
		}

		[[nodiscard]] inline const Actor* IsTurret(const TESObjectREFR* a_refr)
		{
			using func_t = const Actor* (*)(const TESObjectREFR*);
			static REL::Relocation<func_t> func{ ID::Workshop::IsTurretConst };
			return func(a_refr);
		}

		[[nodiscard]] inline bool IsValidMultiSelectItem(TESObjectREFR* a_refr)
		{
			using func_t = decltype(&Workshop::IsValidMultiSelectItem);
			static REL::Relocation<func_t> func{ ID::Workshop::IsValidMultiSelectItem };
			return func(a_refr);
		}

		[[nodiscard]] inline bool IsValidMultiSelectPlacementItem()
		{
			using func_t = decltype(&Workshop::IsValidMultiSelectPlacementItem);
			static REL::Relocation<func_t> func{ ID::Workshop::IsValidMultiSelectPlacementItem };
			return func();
		}

		[[nodiscard]] inline bool IsWorkshopActi(const TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::IsWorkshopActi);
			static REL::Relocation<func_t> func{ ID::Workshop::IsWorkshopActi };
			return func(a_refr);
		}

		[[nodiscard]] inline bool IsWorkshopItem(const TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::IsWorkshopItem);
			static REL::Relocation<func_t> func{ ID::Workshop::IsWorkshopItem };
			return func(a_refr);
		}

		[[nodiscard]] inline bool ItemCanBeMoved(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::ItemCanBeMoved);
			static REL::Relocation<func_t> func{ ID::Workshop::ItemCanBeMoved };
			return func(a_refr);
		}

		[[nodiscard]] inline bool ItemNeedsRepair(const TESObjectREFR* a_refr)
		{
			using func_t = decltype(&Workshop::ItemNeedsRepair);
			static REL::Relocation<func_t> func{ ID::Workshop::ItemNeedsRepair };
			return func(a_refr);
		}

		[[nodiscard]] inline bool ItemStacksWhenSnapped(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::ItemStacksWhenSnapped);
			static REL::Relocation<func_t> func{ ID::Workshop::ItemStacksWhenSnapped };
			return func(a_refr);
		}

		inline void KillSDM()
		{
			using func_t = decltype(&Workshop::KillSDM);
			static REL::Relocation<func_t> func{ ID::Workshop::KillSDM };
			return func();
		}

		inline void MakeReferenceStatic(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::MakeReferenceStatic);
			static REL::Relocation<func_t> func{ ID::Workshop::MakeReferenceStatic };
			return func(a_refr);
		}

		[[nodiscard]] inline bool NewItemQueued()
		{
			using func_t = decltype(&Workshop::NewItemQueued);
			static REL::Relocation<func_t> func{ ID::Workshop::NewItemQueued };
			return func();
		}

		[[nodiscard]] inline bool IsWorkshopItem(TESObjectREFR& a_ref)
		{
			using func_t = decltype(&Workshop::IsWorkshopItem);
			static REL::Relocation<func_t> func{ ID::Workshop::IsWorkshopItem };
			return func(a_ref);
		}

		inline bool PlaceCurrentReference(const ContextData& a_context)
		{
			using func_t = decltype(&Workshop::PlaceCurrentReference);
			static REL::Relocation<func_t> func{ ID::Workshop::PlaceCurrentReference };
			return func(a_context);
		}

		inline void PrepareMovingStackedWires()
		{
			using func_t = decltype(&Workshop::PrepareMovingStackedWires);
			static REL::Relocation<func_t> func{ ID::Workshop::PrepareMovingStackedWires };
			return func();
		}

		inline void PrepareToMoveStackedItem(TESObjectREFR& a_refr, const NiPoint3& a_pos, float a_value)
		{
			using func_t = decltype(&Workshop::PrepareToMoveStackedItem);
			static REL::Relocation<func_t> func{ ID::Workshop::PrepareToMoveStackedItem };
			return func(a_refr, a_pos, a_value);
		}

		inline void ProcessExitWorkshop(const ContextData& a_context, bool a_flag)
		{
			using func_t = decltype(&Workshop::ProcessExitWorkshop);
			static REL::Relocation<func_t> func{ ID::Workshop::ProcessExitWorkshop };
			return func(a_context, a_flag);
		}

		inline void ProcessExpandActiveEdit(const ContextData& a_context)
		{
			using func_t = decltype(&Workshop::ProcessExpandActiveEdit);
			static REL::Relocation<func_t> func{ ID::Workshop::ProcessExpandActiveEdit };
			return func(a_context);
		}

		inline void ProcessResourceRecalculations()
		{
			using func_t = decltype(&Workshop::ProcessResourceRecalculations);
			static REL::Relocation<func_t> func{ ID::Workshop::ProcessResourceRecalculations };
			return func();
		}

		[[nodiscard]] inline const BSTArray<ObjectRefHandle>& QAllWorkshopsArray()
		{
			using func_t = decltype(&Workshop::QAllWorkshopsArray);
			static REL::Relocation<func_t> func{ ID::Workshop::QAllWorkshopsArray };
			return func();
		}

		[[nodiscard]] inline bool QEnabled()
		{
			using func_t = decltype(&Workshop::QEnabled);
			static REL::Relocation<func_t> func{ ID::Workshop::QEnabled };
			return func();
		}

		[[nodiscard]] inline bool QNewItemMode()
		{
			using func_t = decltype(&Workshop::QNewItemMode);
			static REL::Relocation<func_t> func{ ID::Workshop::QNewItemMode };
			return func();
		}

		[[nodiscard]] inline BSPointerHandle<TESObjectREFR, BSUntypedPointerHandle<21, 5>> QSharedWorkshopContainer()
		{
			using func_t = decltype(&Workshop::QSharedWorkshopContainer);
			static REL::Relocation<func_t> func{ ID::Workshop::QSharedWorkshopContainer };
			return func();
		}

		inline void QueueDropUnsupportedItem(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::QueueDropUnsupportedItem);
			static REL::Relocation<func_t> func{ ID::Workshop::QueueDropUnsupportedItem };
			return func(a_refr);
		}

		inline void QueueResourceRecalculation(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::QueueResourceRecalculation);
			static REL::Relocation<func_t> func{ ID::Workshop::QueueResourceRecalculation };
			return func(a_refr);
		}

		inline void QueueUpdateItemPosition(TESObjectREFR& a_refr, bool a_flag)
		{
			using func_t = decltype(&Workshop::QueueUpdateItemPosition);
			static REL::Relocation<func_t> func{ ID::Workshop::QueueUpdateItemPosition };
			return func(a_refr, a_flag);
		}

		inline void RecalculateResources(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::RecalculateResources);
			static REL::Relocation<func_t> func{ ID::Workshop::RecalculateResources };
			return func(a_refr);
		}

		inline void RefillSharedWorkshopContainer()
		{
			using func_t = decltype(&Workshop::RefillSharedWorkshopContainer);
			static REL::Relocation<func_t> func{ ID::Workshop::RefillSharedWorkshopContainer };
			return func();
		}

		inline void RegisterForBuildableAreaEvent(BSTEventSink<BuildableAreaEvent>* a_sink)
		{
			using func_t = decltype(&Workshop::RegisterForBuildableAreaEvent);
			static REL::Relocation<func_t> func{ ID::Workshop::RegisterForBuildableAreaEvent };
			return func(a_sink);
		}

		inline void RegisterForItemDestroyed(BSTEventSink<ItemDestroyedEvent>* a_sink)
		{
			using func_t = decltype(&Workshop::RegisterForItemDestroyed);
			static REL::Relocation<func_t> func{ ID::Workshop::RegisterForItemDestroyed };
			return func(a_sink);
		}

		inline void RegisterForItemGrabbed(BSTEventSink<ItemGrabbedEvent>* a_sink)
		{
			using func_t = decltype(&Workshop::RegisterForItemGrabbed);
			static REL::Relocation<func_t> func{ ID::Workshop::RegisterForItemGrabbed };
			return func(a_sink);
		}

		inline void RegisterForItemMoved(BSTEventSink<ItemMovedEvent>* a_sink)
		{
			using func_t = decltype(&Workshop::RegisterForItemMoved);
			static REL::Relocation<func_t> func{ ID::Workshop::RegisterForItemMoved };
			return func(a_sink);
		}

		inline void RegisterForItemPlaced(BSTEventSink<ItemPlacedEvent>* a_sink)
		{
			using func_t = decltype(&Workshop::RegisterForItemPlaced);
			static REL::Relocation<func_t> func{ ID::Workshop::RegisterForItemPlaced };
			return func(a_sink);
		}

		inline void RegisterForItemRepaired(BSTEventSink<ItemRepairedEvent>* a_sink)
		{
			using func_t = decltype(&Workshop::RegisterForItemRepaired);
			static REL::Relocation<func_t> func{ ID::Workshop::RegisterForItemRepaired };
			return func(a_sink);
		}

		inline void RegisterForItemScrappedEvent(BSTEventSink<ItemScrappedEvent>* a_sink)
		{
			using func_t = decltype(&Workshop::RegisterForItemScrappedEvent);
			static REL::Relocation<func_t> func{ ID::Workshop::RegisterForItemScrappedEvent };
			return func(a_sink);
		}

		inline void RegisterForPickRefChangeEvent(BSTEventSink<PickRefUpdateEvent>* a_sink)
		{
			using func_t = decltype(&Workshop::RegisterForPickRefChangeEvent);
			static REL::Relocation<func_t> func{ ID::Workshop::RegisterForPickRefChangeEvent };
			return func(a_sink);
		}

		inline void RegisterForPlacementStatusEvent(BSTEventSink<PlacementStatusEvent>* a_sink)
		{
			using func_t = decltype(&Workshop::RegisterForPlacementStatusEvent);
			static REL::Relocation<func_t> func{ ID::Workshop::RegisterForPlacementStatusEvent };
			return func(a_sink);
		}

		inline void RegisterForPowerOff(BSTEventSink<PowerOffEvent>* a_sink)
		{
			using func_t = decltype(&Workshop::RegisterForPowerOff);
			static REL::Relocation<func_t> func{ ID::Workshop::RegisterForPowerOff };
			return func(a_sink);
		}

		inline void RegisterForPowerOn(BSTEventSink<PowerOnEvent>* a_sink)
		{
			using func_t = decltype(&Workshop::RegisterForPowerOn);
			static REL::Relocation<func_t> func{ ID::Workshop::RegisterForPowerOn };
			return func(a_sink);
		}

		inline void RegisterForWorkshopModeEvent(BSTEventSink<WorkshopModeEvent>* a_sink)
		{
			using func_t = decltype(&Workshop::RegisterForWorkshopModeEvent);
			static REL::Relocation<func_t> func{ ID::Workshop::RegisterForWorkshopModeEvent };
			return func(a_sink);
		}

		inline void RemoveItemFromWorkshopContainers(TESBoundObject* a_object, std::uint32_t a_count)
		{
			using func_t = decltype(&Workshop::RemoveItemFromWorkshopContainers);
			static REL::Relocation<func_t> func{ ID::Workshop::RemoveItemFromWorkshopContainers };
			return func(a_object, a_count);
		}

		inline void Repair(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::Repair);
			static REL::Relocation<func_t> func{ ID::Workshop::Repair };
			return func(a_refr);
		}

		inline void RequestExitWorkshop(bool a_allowReEntry)
		{
			using func_t = decltype(&Workshop::RequestExitWorkshop);
			static REL::Relocation<func_t> func{ ID::Workshop::RequestExitWorkshop };
			return func(a_allowReEntry);
		}

		[[nodiscard]] inline bool RequestRepairItem(const ContextData& a_context)
		{
			using func_t = decltype(&Workshop::RequestRepairItem);
			static REL::Relocation<func_t> func{ ID::Workshop::RequestRepairItem };
			return func(a_context);
		}

		[[nodiscard]] inline bool RequestScrapPlacementItem(const ContextData& a_context)
		{
			using func_t = decltype(&Workshop::RequestScrapPlacementItem);
			static REL::Relocation<func_t> func{ ID::Workshop::RequestScrapPlacementItem };
			return func(a_context);
		}

		inline void RequestScrapRef(TESObjectREFR& a_refr, const ContextData& a_context)
		{
			using func_t = decltype(&Workshop::RequestScrapRef);
			static REL::Relocation<func_t> func{ ID::Workshop::RequestScrapRef };
			return func(a_refr, a_context);
		}

		inline void RequestStorePlacementItem(const ContextData& a_context)
		{
			using func_t = decltype(&Workshop::RequestStorePlacementItem);
			static REL::Relocation<func_t> func{ ID::Workshop::RequestStorePlacementItem };
			return func(a_context);
		}

		inline void ResetItemLocalSpaceTransl()
		{
			using func_t = decltype(&Workshop::ResetItemLocalSpaceTransl);
			static REL::Relocation<func_t> func{ ID::Workshop::ResetItemLocalSpaceTransl };
			return func();
		}

		inline void RevertMovingStackedItems()
		{
			using func_t = decltype(&Workshop::RevertMovingStackedItems);
			static REL::Relocation<func_t> func{ ID::Workshop::RevertMovingStackedItems };
			return func();
		}

		inline void RunBedChecks(TESObjectREFR* a_refr)
		{
			using func_t = decltype(&Workshop::RunBedChecks);
			static REL::Relocation<func_t> func{ ID::Workshop::RunBedChecks };
			return func(a_refr);
		}

		inline void ScrapAll(std::uint32_t& a_scrappedCount, std::uint32_t& a_totalCount)
		{
			using func_t = decltype(&Workshop::ScrapAll);
			static REL::Relocation<func_t> func{ ID::Workshop::ScrapAll };
			return func(a_scrappedCount, a_totalCount);
		}

		inline void ScrapReference(const ContextData& a_context, BSPointerHandleSmartPointer<BSPointerHandleManagerInterface<TESObjectREFR, HandleManager>>& a_scrapRef, BSTArray<BSTTuple<TESBoundObject*, std::uint32_t>>* a_rewards)
		{
			using func_t = decltype(&Workshop::ScrapReference);
			static REL::Relocation<func_t> func{ ID::Workshop::ScrapReference };
			return func(a_context, a_scrapRef, a_rewards);
		}

		inline void SendItemScrappedEvent()
		{
			using func_t = decltype(&Workshop::SendItemScrappedEvent);
			static REL::Relocation<func_t> func{ ID::Workshop::SendItemScrappedEvent };
			return func();
		}

		inline void SetAdjustmentMode(const ContextData& a_context, bool a_flag)
		{
			using func_t = decltype(&Workshop::SetAdjustmentMode);
			static REL::Relocation<func_t> func{ ID::Workshop::SetAdjustmentMode };
			return func(a_context, a_flag);
		}

		inline void SetBuildableAreaVisible(TESObjectREFR& a_refr, bool a_visible)
		{
			using func_t = decltype(&Workshop::SetBuildableAreaVisible);
			static REL::Relocation<func_t> func{ ID::Workshop::SetBuildableAreaVisible };
			return func(a_refr, a_visible);
		}

		inline void SetIsWorkshopItem(TESObjectREFR& a_refr, bool a_isWorkshopItem, TESObjectREFR* a_workshop)
		{
			using func_t = decltype(&Workshop::SetIsWorkshopItem);
			static REL::Relocation<func_t> func{ ID::Workshop::SetIsWorkshopItem };
			return func(a_refr, a_isWorkshopItem, a_workshop);
		}

		inline void SetPowerConnectionItem(BSPointerHandle<TESObjectREFR, BSUntypedPointerHandle<21, 5>> a_handle)
		{
			using func_t = decltype(&Workshop::SetPowerConnectionItem);
			static REL::Relocation<func_t> func{ ID::Workshop::SetPowerConnectionItem };
			return func(a_handle);
		}

		inline void SetPowerConnectionType(std::uint32_t a_count)
		{
			using func_t = decltype(&Workshop::SetPowerConnectionType);
			static REL::Relocation<func_t> func{ ID::Workshop::SetPowerConnectionType };
			return func(a_count);
		}

		inline void SetSelectedEditItem(ObjectRefHandle a_refr)
		{
			using func_t = decltype(&Workshop::SetSelectedEditItem);
			static REL::Relocation<func_t> func{ ID::Workshop::SetSelectedEditItem };
			return func(a_refr);
		}

		inline void SetSnapInfo(
			TESObjectREFR&                                                                   a_refr,
			const BSTSmartPointer<BSConnectPoint::Parent, BSTSmartPointerIntrusiveRefCount>& a_snapParent,
			const BSTSmartPointer<BSConnectPoint::Parent, BSTSmartPointerIntrusiveRefCount>& a_prevSnapParent)
		{
			using func_t = decltype(&Workshop::SetSnapInfo);
			static REL::Relocation<func_t> func{ ID::Workshop::SetSnapInfo };
			return func(a_refr, a_snapParent, a_prevSnapParent);
		}

		inline void SetWorkshopAdjustInputMode(bool a_flag)
		{
			using func_t = decltype(&Workshop::SetWorkshopAdjustInputMode);
			static REL::Relocation<func_t> func{ ID::Workshop::SetWorkshopAdjustInputMode };
			return func(a_flag);
		}

		[[nodiscard]] inline bool ShouldHideHappinessBar(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::ShouldHideHappinessBar);
			static REL::Relocation<func_t> func{ ID::Workshop::ShouldHideHappinessBar };
			return func(a_refr);
		}

		inline void StartBuildTimer(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::StartBuildTimer);
			static REL::Relocation<func_t> func{ ID::Workshop::StartBuildTimer };
			return func(a_refr);
		}

		[[nodiscard]] inline TESObjectREFR* StartNearbyWorkshop(StartWorkshopStatus& a_status)
		{
			using func_t = decltype(&Workshop::StartNearbyWorkshop);
			static REL::Relocation<func_t> func{ ID::Workshop::StartNearbyWorkshop };
			return func(a_status);
		}

		inline void StartWorkshop(TESObjectREFR* a_workshopRef)
		{
			using func_t = decltype(&Workshop::StartWorkshop);
			static REL::Relocation<func_t> func{ ID::Workshop::StartWorkshop };
			return func(a_workshopRef);
		}

		inline void ToggleDropMode()
		{
			using func_t = decltype(&Workshop::ToggleDropMode);
			static REL::Relocation<func_t> func{ ID::Workshop::ToggleDropMode };
			return func();
		}

		inline void ToggleEditMode(const ContextData& a_context)
		{
			using func_t = decltype(&Workshop::ToggleEditMode);
			static REL::Relocation<func_t> func{ ID::Workshop::ToggleEditMode };
			return func(a_context);
		}

		inline void ToggleWorkshopMode(const ContextData& a_context, TESObjectREFR* a_workshopRef)
		{
			using func_t = decltype(&Workshop::ToggleWorkshopMode);
			static REL::Relocation<func_t> func{ ID::Workshop::ToggleWorkshopMode };
			return func(a_context, a_workshopRef);
		}

		inline void UnregisterForBuildableAreaEvent(BSTEventSink<BuildableAreaEvent>* a_sink)
		{
			using func_t = decltype(&Workshop::UnregisterForBuildableAreaEvent);
			static REL::Relocation<func_t> func{ ID::Workshop::UnregisterForBuildableAreaEvent };
			return func(a_sink);
		}

		inline void UnregisterForItemDestroyed(BSTEventSink<ItemDestroyedEvent>* a_sink)
		{
			using func_t = decltype(&Workshop::UnregisterForItemDestroyed);
			static REL::Relocation<func_t> func{ ID::Workshop::UnregisterForItemDestroyed };
			return func(a_sink);
		}

		inline void UnregisterForItemGrabbed(BSTEventSink<ItemGrabbedEvent>* a_sink)
		{
			using func_t = decltype(&Workshop::UnregisterForItemGrabbed);
			static REL::Relocation<func_t> func{ ID::Workshop::UnregisterForItemGrabbed };
			return func(a_sink);
		}

		inline void UnregisterForItemMoved(BSTEventSink<ItemMovedEvent>* a_sink)
		{
			using func_t = decltype(&Workshop::UnregisterForItemMoved);
			static REL::Relocation<func_t> func{ ID::Workshop::UnregisterForItemMoved };
			return func(a_sink);
		}

		inline void UnregisterForItemPlaced(BSTEventSink<ItemPlacedEvent>* a_sink)
		{
			using func_t = decltype(&Workshop::UnregisterForItemPlaced);
			static REL::Relocation<func_t> func{ ID::Workshop::UnregisterForItemPlaced };
			return func(a_sink);
		}

		inline void UnregisterForItemRepaired(BSTEventSink<ItemRepairedEvent>* a_sink)
		{
			using func_t = decltype(&Workshop::UnregisterForItemRepaired);
			static REL::Relocation<func_t> func{ ID::Workshop::UnregisterForItemRepaired };
			return func(a_sink);
		}

		inline void UnregisterForItemScrappedEvent(BSTEventSink<ItemScrappedEvent>* a_sink)
		{
			using func_t = decltype(&Workshop::UnregisterForItemScrappedEvent);
			static REL::Relocation<func_t> func{ ID::Workshop::UnregisterForItemScrappedEvent };
			return func(a_sink);
		}

		inline void UnregisterForPickRefChangeEvent(BSTEventSink<PickRefUpdateEvent>* a_sink)
		{
			using func_t = decltype(&Workshop::UnregisterForPickRefChangeEvent);
			static REL::Relocation<func_t> func{ ID::Workshop::UnregisterForPickRefChangeEvent };
			return func(a_sink);
		}

		inline void UnregisterForPlacementStatusEvent(BSTEventSink<PlacementStatusEvent>* a_sink)
		{
			using func_t = decltype(&Workshop::UnregisterForPlacementStatusEvent);
			static REL::Relocation<func_t> func{ ID::Workshop::UnregisterForPlacementStatusEvent };
			return func(a_sink);
		}

		inline void UnregisterForPowerOff(BSTEventSink<PowerOffEvent>* a_sink)
		{
			using func_t = decltype(&Workshop::UnregisterForPowerOff);
			static REL::Relocation<func_t> func{ ID::Workshop::UnregisterForPowerOff };
			return func(a_sink);
		}

		inline void UnregisterForPowerOn(BSTEventSink<PowerOnEvent>* a_sink)
		{
			using func_t = decltype(&Workshop::UnregisterForPowerOn);
			static REL::Relocation<func_t> func{ ID::Workshop::UnregisterForPowerOn };
			return func(a_sink);
		}

		inline void UnregisterForWorkshopModeEvent(BSTEventSink<WorkshopModeEvent>* a_sink)
		{
			using func_t = decltype(&Workshop::UnregisterForWorkshopModeEvent);
			static REL::Relocation<func_t> func{ ID::Workshop::UnregisterForWorkshopModeEvent };
			return func(a_sink);
		}

		inline void UnstackItem(TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::UnstackItem);
			static REL::Relocation<func_t> func{ ID::Workshop::UnstackItem };
			return func(a_refr);
		}

		inline void Update(const ContextData& a_context)
		{
			using func_t = decltype(&Workshop::Update);
			static REL::Relocation<func_t> func{ ID::Workshop::Update };
			return func(a_context);
		}

		inline void UpdateActiveEdit(const ContextData& a_context, bool a_multiselect = false)
		{
			using func_t = decltype(&Workshop::UpdateActiveEdit);
			static REL::Relocation<func_t> func{ ID::Workshop::UpdateActiveEdit };
			return func(a_context, a_multiselect);
		}

		[[nodiscard]] inline bool UpdateAttachedSplines(const ContextData& a_context, TESObjectREFR* a_refr)
		{
			using func_t = decltype(&Workshop::UpdateAttachedSplines);
			static REL::Relocation<func_t> func{ ID::Workshop::UpdateAttachedSplines };
			return func(a_context, a_refr);
		}

		inline void UpdateAttachRefChildrenTransform(TESObjectREFR* a_refr)
		{
			using func_t = decltype(&Workshop::UpdateAttachRefChildrenTransform);
			static REL::Relocation<func_t> func{ ID::Workshop::UpdateAttachRefChildrenTransform };
			return func(a_refr);
		}

		inline void UpdateForegroundReferenceJob(const ContextData& a_context)
		{
			using func_t = decltype(&Workshop::UpdateForegroundReferenceJob);
			static REL::Relocation<func_t> func{ ID::Workshop::UpdateForegroundReferenceJob };
			return func(a_context);
		}

		inline void UpdateItemHoldDistance(const ContextData& a_context, bool a_flag, float a_value)
		{
			using func_t = decltype(&Workshop::UpdateItemHoldDistance);
			static REL::Relocation<func_t> func{ ID::Workshop::UpdateItemHoldDistance };
			return func(a_context, a_flag, a_value);
		}

		inline void UpdateItemPanDistance(const ContextData& a_context, bool a_flag, float a_value)
		{
			using func_t = decltype(&Workshop::UpdateItemPanDistance);
			static REL::Relocation<func_t> func{ ID::Workshop::UpdateItemPanDistance };
			return func(a_context, a_flag, a_value);
		}

		inline void UpdateItemPositions()
		{
			using func_t = decltype(&Workshop::UpdateItemPositions);
			static REL::Relocation<func_t> func{ ID::Workshop::UpdateItemPositions };
			return func();
		}

		inline void UpdateItemVerticalDistance(const ContextData& a_context, bool a_flag, float a_value)
		{
			using func_t = decltype(&Workshop::UpdateItemVerticalDistance);
			static REL::Relocation<func_t> func{ ID::Workshop::UpdateItemVerticalDistance };
			return func(a_context, a_flag, a_value);
		}

		inline void UpdateItemZRot(bool a_positive, float a_scale, bool a_cycleSnapCandidate)
		{
			using func_t = decltype(&Workshop::UpdateItemZRot);
			static REL::Relocation<func_t> func{ ID::Workshop::UpdateItemZRot };
			return func(a_positive, a_scale, a_cycleSnapCandidate);
		}

		inline void UpdateMovingStackedItems(const TESObjectREFR& a_refr, const NiPoint3& a_pos, float a_value)
		{
			using func_t = decltype(&Workshop::UpdateMovingStackedItems);
			static REL::Relocation<func_t> func{ ID::Workshop::UpdateMovingStackedItems };
			return func(a_refr, a_pos, a_value);
		}

		inline void UpdateOffline()
		{
			using func_t = decltype(&Workshop::UpdateOffline);
			static REL::Relocation<func_t> func{ ID::Workshop::UpdateOffline };
			return func();
		}

		inline void UpdatePlacementItemTransl(const NiPoint3& a_pos, const ContextData& a_context)
		{
			using func_t = decltype(&Workshop::UpdatePlacementItemTransl);
			static REL::Relocation<func_t> func{ ID::Workshop::UpdatePlacementItemTransl };
			return func(a_pos, a_context);
		}

		[[nodiscard]] inline bool WorkshopCanCreateRef(const TESObjectREFR* a_refr, const TESObjectREFR& a_refr2)
		{
			using func_t = decltype(&Workshop::WorkshopCanCreateRef);
			static REL::Relocation<func_t> func{ ID::Workshop::WorkshopCanCreateRef };
			return func(a_refr, a_refr2);
		}

		[[nodiscard]] inline bool WorkshopCanScrapRef(const TESObjectREFR& a_refr, bool a_ignoreOwnership)
		{
			using func_t = decltype(&Workshop::WorkshopCanScrapRef);
			static REL::Relocation<func_t> func{ ID::Workshop::WorkshopCanScrapRef };
			return func(a_refr, a_ignoreOwnership);
		}

		[[nodiscard]] inline bool WorkshopCanSelectRef(const TESObjectREFR& a_refr)
		{
			using func_t = decltype(&Workshop::WorkshopCanSelectRef);
			static REL::Relocation<func_t> func{ ID::Workshop::WorkshopCanSelectRef };
			return func(a_refr);
		}

		[[nodiscard]] inline bool WorkshopCanShowRecipe(BGSConstructibleObject* a_recipe, BGSKeyword* a_filter)
		{
			using func_t = decltype(&Workshop::WorkshopCanShowRecipe);
			static REL::Relocation<func_t> func{ ID::Workshop::WorkshopCanShowRecipe };
			return func(a_recipe, a_filter);
		}

		[[nodiscard]] inline PlacementItemData* GetCurrentPlacementItemData()
		{
			static REL::Relocation<PlacementItemData*> value{ ID::Workshop::CurrentPlacementItemData };
			return value.get();
		}

		[[nodiscard]] inline std::uint16_t* GetCurrentRow()
		{
			static REL::Relocation<std::uint16_t*> value{ ID::Workshop::CurrentRow };
			return value.get();
		}

		[[nodiscard]] inline ObjectRefHandle* GetPlacementItem()
		{
			static REL::Relocation<ObjectRefHandle*> value{ ID::Workshop::PlacementItem };
			return value.get();
		}

		[[nodiscard]] inline std::uint32_t* GetPlacementCollisionCount()
		{
			static REL::Relocation<std::uint32_t*> value{ ID::Workshop::PlacementCollisionCount };
			return value.get();
		}
	}
}
