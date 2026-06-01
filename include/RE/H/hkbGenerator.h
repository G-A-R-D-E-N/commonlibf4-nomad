#pragma once

#include "RE/H/hkbNode.h"
#include "RE/IDs_RTTI.h"
#include "RE/IDs_VTABLE.h"

namespace RE
{
class __declspec(novtable) hkbGenerator : public hkbNode
{
  public:
    static constexpr auto RTTI{RTTI::hkbGenerator};
    static constexpr auto VTABLE{VTABLE::hkbGenerator};
};
} // namespace RE
