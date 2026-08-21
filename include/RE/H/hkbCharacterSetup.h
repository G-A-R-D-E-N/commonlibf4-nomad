#pragma once

#include "RE/H/hkReferencedObject.h"
#include "RE/IDs_RTTI.h"
#include "RE/IDs_VTABLE.h"

namespace RE
{
class hkbCharacterData;

class __declspec(novtable) hkbCharacterSetup : public hkReferencedObject
{
  public:
    static constexpr auto RTTI{RTTI::hkbCharacterSetup};
    static constexpr auto VTABLE{VTABLE::hkbCharacterSetup};

    [[nodiscard]] hkbCharacterData *GetData() const noexcept
    {
        return data;
    }

    // members
    std::uint8_t pad10[0x40 - 0x10]; // 10
    hkbCharacterData *data;          // 40
};
static_assert(offsetof(hkbCharacterSetup, data) == 0x40);
} // namespace RE
