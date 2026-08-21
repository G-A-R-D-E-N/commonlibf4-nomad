#pragma once

#include "REL/Relocation.h"

#include "RE/H/hkArray.h"
#include "RE/H/hkContainerTempAllocator.h"
#include "RE/IDs.h"

namespace RE
{
class hkbBehaviorGraph;
class hkbNode;

namespace hkbUtils
{
struct NodeBehaviorPair
{
    // members
    hkbNode *node;              // 00
    hkbBehaviorGraph *behavior; // 08
};
static_assert(sizeof(NodeBehaviorPair) == 0x10);

inline void collectNodesLeafFirst(hkbNode *a_root, const hkbBehaviorGraph *a_behavior, std::int32_t a_initialDepth,
                                  hkArray<NodeBehaviorPair, hkContainerTempAllocator> &a_nodes)
{
    using func_t = decltype(&collectNodesLeafFirst);
    static REL::Relocation<func_t> func{ID::hkbUtils::collectNodesLeafFirst};
    return func(a_root, a_behavior, a_initialDepth, a_nodes);
}
} // namespace hkbUtils
} // namespace RE
