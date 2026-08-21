#pragma once

#include "RE/H/hkReferencedObject.h"
#include "RE/IDs_RTTI.h"
#include "RE/IDs_VTABLE.h"

namespace RE
{
class hkaAnimation;

class __declspec(novtable) hkaAnimationBinding : public hkReferencedObject
{
  public:
    static constexpr auto RTTI{RTTI::hkaAnimationBinding};
    static constexpr auto VTABLE{VTABLE::hkaAnimationBinding};

    // members
    std::uint8_t pad10[0x18 - 0x10]; // 10
    hkaAnimation *animation;         // 18
};
static_assert(offsetof(hkaAnimationBinding, animation) == 0x18);

class __declspec(novtable) hkaAnimationControl : public hkReferencedObject
{
  public:
    static constexpr auto RTTI{RTTI::hkaAnimationControl};
    static constexpr auto VTABLE{VTABLE::hkaAnimationControl};

    // members
    float time;                                  // 10
    float weight;                                // 14
    std::uint8_t pad18[0x38 - 0x18];             // 18
    const hkaAnimationBinding *animationBinding; // 38
};
static_assert(offsetof(hkaAnimationControl, time) == 0x10);
static_assert(offsetof(hkaAnimationControl, animationBinding) == 0x38);

class __declspec(novtable) hkaDefaultAnimationControl : public hkaAnimationControl
{
  public:
    static constexpr auto RTTI{RTTI::hkaDefaultAnimationControl};
    static constexpr auto VTABLE{VTABLE::hkaDefaultAnimationControl};

    // members
    std::uint8_t pad40[0x9C - 0x40]; // 40
    float cropStartAmountLocalTime;  // 9C
    float cropEndAmountLocalTime;    // A0
};
static_assert(offsetof(hkaDefaultAnimationControl, cropStartAmountLocalTime) == 0x9C);
static_assert(offsetof(hkaDefaultAnimationControl, cropEndAmountLocalTime) == 0xA0);
} // namespace RE
