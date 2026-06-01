#pragma once

#include "RE/H/hkReferencedObject.h"
#include "RE/IDs_RTTI.h"
#include "RE/IDs_VTABLE.h"

namespace RE
{
class __declspec(novtable) hkbNode : public hkReferencedObject
{
  public:
    static constexpr auto RTTI{RTTI::hkbNode};
    static constexpr auto VTABLE{VTABLE::hkbNode};
};
} // namespace RE
