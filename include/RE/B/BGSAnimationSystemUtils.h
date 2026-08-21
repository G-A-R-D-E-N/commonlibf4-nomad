#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTObjectArena.h"
#include "RE/B/BSTTuple.h"
#include "RE/S/SubgraphHandle.h"

namespace RE
{
class Actor;
class IAnimationGraphManagerHolder;
enum class IO_TASK_PRIORITY;

namespace BGSAnimationSystemUtils
{
class ActiveSyncInfo
{
  public:
    // members
    BSTObjectArena<BSTTuple<BSFixedString, float>> otherSyncInfo; // 00
    float currentAnimTime;                                        // 40
    float animSpeedMult;                                          // 44
    float totalAnimTime;                                          // 48
};
static_assert(sizeof(ActiveSyncInfo) == 0x50);

inline bool GetActiveSyncInfo(const IAnimationGraphManagerHolder *a_graphHolder, ActiveSyncInfo &a_infoOut)
{
    using func_t = decltype(&GetActiveSyncInfo);
    static REL::Relocation<func_t> func{ID::BGSAnimationSystemUtils::GetActiveSyncInfo};
    return func(a_graphHolder, a_infoOut);
}

inline bool InitializeActorInstant(Actor &a_actor, bool a_update3D)
{
    using func_t = decltype(&InitializeActorInstant);
    static REL::Relocation<func_t> func{ID::BGSAnimationSystemUtils::InitializeActorInstant};
    return func(a_actor, a_update3D);
}

inline bool IsActiveGraphInTransition(const TESObjectREFR *a_refr)
{
    using func_t = decltype(&IsActiveGraphInTransition);
    static REL::Relocation<func_t> func{ID::BGSAnimationSystemUtils::IsActiveGraphInTransition};
    return func(a_refr);
}

inline bool IsAnimationSubGraphLoaded(const Actor &a_actor, const BSTSmallArray<SubgraphHandle, 2> &a_handles,
                                      const IO_TASK_PRIORITY &a_priority)
{
    using func_t = decltype(&IsAnimationSubGraphLoaded);
    static REL::Relocation<func_t> func{ID::BGSAnimationSystemUtils::IsAnimationSubGraphLoaded};
    return func(a_actor, a_handles, a_priority);
}
} // namespace BGSAnimationSystemUtils
} // namespace RE
