#pragma once

#include "RE/H/hkReferencedObject.h"
#include "RE/IDs_RTTI.h"
#include "RE/IDs_VTABLE.h"

namespace RE
{
class hkbCharacterStringData;

class __declspec(novtable) hkbCharacterData : public hkReferencedObject
{
  public:
    static constexpr auto RTTI{RTTI::hkbCharacterData};
    static constexpr auto VTABLE{VTABLE::hkbCharacterData};

    [[nodiscard]] hkbCharacterStringData *GetStringData() const noexcept
    {
        return stringData;
    }

    // members
    std::uint8_t pad10[0xB0 - 0x10];    // 010
    hkbCharacterStringData *stringData; // 0B0
};
static_assert(offsetof(hkbCharacterData, stringData) == 0xB0);
} // namespace RE
