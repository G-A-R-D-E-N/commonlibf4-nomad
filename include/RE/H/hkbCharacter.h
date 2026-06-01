#pragma once

#include "RE/H/hkReferencedObject.h"
#include "RE/IDs_RTTI.h"
#include "RE/IDs_VTABLE.h"

namespace RE
{
class hkbBehaviorGraph;

class __declspec(novtable) hkbCharacter : public hkReferencedObject
{
  public:
    static constexpr auto RTTI{RTTI::hkbCharacter};
    static constexpr auto VTABLE{VTABLE::hkbCharacter};

    // members
    std::uint8_t pad10[0x70];        // 10
    hkbBehaviorGraph *behaviorGraph; // 80
};
static_assert(offsetof(hkbCharacter, behaviorGraph) == 0x80);
} // namespace RE
