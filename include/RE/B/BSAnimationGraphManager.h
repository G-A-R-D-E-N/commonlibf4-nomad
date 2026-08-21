#pragma once

#include "RE/B/BSAnimationGraphVariableCache.h"
#include "RE/B/BSFixedString.h"
#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/B/BSSpinLock.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/B/BSTTuple.h"

namespace RE
{
class BSAnimationGraphChannel;
class BShkbAnimationGraph;
class BSAnimationGraphEvent;
class BSAnimationUpdateData;
class NiAVObject;

class BSAnimationGraphManager : public BSTEventSink<BSAnimationGraphEvent>, // 00
                                public BSIntrusiveRefCounted                // 08
{
  public:
    class DependentManagerSmartPtr
    {
      public:
        // members
        std::uint64_t ptrAndFlagsStorage; // 00
    };
    static_assert(sizeof(DependentManagerSmartPtr) == 0x08);

    [[nodiscard]] bool SetTargets(const BSScrapArray<NiAVObject *> &a_targets, bool a_attaching)
    {
        using func_t = decltype(&BSAnimationGraphManager::SetTargets);
        static REL::Relocation<func_t> func{ID::BSAnimationGraphManager::SetTargets};
        return func(this, a_targets, a_attaching);
    }

    void Update(const BSAnimationUpdateData &a_updateData)
    {
        using func_t = decltype(&BSAnimationGraphManager::Update);
        static REL::Relocation<func_t> func{ID::BSAnimationGraphManager::Update};
        return func(this, a_updateData);
    }

    // members
    BSTArray<BSTSmartPointer<BSAnimationGraphChannel>> boundChannel;  // 10
    BSTArray<BSTSmartPointer<BSAnimationGraphChannel>> bumpedChannel; // 28
    BSTSmallArray<BSTSmartPointer<BShkbAnimationGraph>, 1> graph;     // 40
    BSTArray<DependentManagerSmartPtr> subManagers;                   // 58
    BSTArray<BSTTuple<BSFixedString, BSFixedString>> eventQueuea;     // 70
    BSAnimationGraphVariableCache variableCache;                      // 88
    BSSpinLock updateLock;                                            // C8
    BSSpinLock dependentManagerLock;                                  // D0
    std::uint32_t activeGraph;                                        // D8
    std::uint32_t generateDepth;                                      // DC
};
static_assert(sizeof(BSAnimationGraphManager) == 0xE0);
} // namespace RE
