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

    [[nodiscard]] hkArray<hkbNodeInfo *> *GetActiveNodes()
    {
        return *reinterpret_cast<hkArray<hkbNodeInfo *> **>(reinterpret_cast<std::uintptr_t>(this) + 0xE0);
    }
};
} // namespace RE
