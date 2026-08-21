#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkbGenerator.h"
#include "RE/IDs_RTTI.h"
#include "RE/IDs_VTABLE.h"

namespace RE
{
struct hkbNodeInfo;

class __declspec(novtable) hkbBehaviorGraph : public hkbGenerator
{
  public:
    static constexpr auto RTTI{RTTI::hkbBehaviorGraph};
    static constexpr auto VTABLE{VTABLE::hkbBehaviorGraph};

    [[nodiscard]] hkbGenerator *GetRootGenerator()
    {
        return rootGenerator;
    }

    [[nodiscard]] hkArray<hkbNodeInfo *> *GetActiveNodes()
    {
        return activeNodes;
    }

    // members
    std::uint8_t pad10[0xC0 - 0x10];     // 10
    hkbGenerator *rootGenerator;         // C0
    std::uint8_t padC8[0xE0 - 0xC8];     // C8
    hkArray<hkbNodeInfo *> *activeNodes; // E0
};
static_assert(offsetof(hkbBehaviorGraph, rootGenerator) == 0xC0);
static_assert(offsetof(hkbBehaviorGraph, activeNodes) == 0xE0);
} // namespace RE
