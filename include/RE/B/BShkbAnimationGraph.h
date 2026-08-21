#pragma once

#include "RE/H/hkbCharacter.h"
#include "RE/IDs_RTTI.h"
#include "RE/IDs_VTABLE.h"

namespace RE
{
class BShkbAnimationGraph
{
  public:
    static constexpr auto RTTI{RTTI::BShkbAnimationGraph};
    static constexpr auto VTABLE{VTABLE::BShkbAnimationGraph};

    [[nodiscard]] bool InitImpl(const char *a_projectPath)
    {
        using func_t = decltype(&BShkbAnimationGraph::InitImpl);
        static REL::Relocation<func_t> func{ID::BShkbAnimationGraph::InitImpl};
        return func(this, a_projectPath);
    }

    [[nodiscard]] hkbCharacter &QCharacter()
    {
        return *reinterpret_cast<hkbCharacter *>(reinterpret_cast<std::uintptr_t>(this) + 0x1C8);
    }

    [[nodiscard]] const hkbCharacter &QCharacter() const
    {
        return *reinterpret_cast<const hkbCharacter *>(reinterpret_cast<std::uintptr_t>(this) + 0x1C8);
    }
};
} // namespace RE
