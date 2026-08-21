#pragma once

#include "RE/H/hkMemoryAllocator.h"

namespace RE
{
class hkContainerTempAllocator
{
  public:
    class Allocator : public hkMemoryAllocator
    {
      public:
    };
    static_assert(sizeof(Allocator) == 0x08);
};
static_assert(std::is_empty_v<hkContainerTempAllocator>);
} // namespace RE
