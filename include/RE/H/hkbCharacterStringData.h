#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkStringPtr.h"
#include "RE/IDs_RTTI.h"
#include "RE/IDs_VTABLE.h"

namespace RE
{
class __declspec(novtable) hkbCharacterStringData : public hkReferencedObject
{
  public:
    static constexpr auto RTTI{RTTI::hkbCharacterStringData};
    static constexpr auto VTABLE{VTABLE::hkbCharacterStringData};

    struct AnimationBundleStringData
    {
        // members
        hkStringPtr bundleName;       // 00
        hkArray<hkStringPtr> strings; // 08
    };
    static_assert(sizeof(AnimationBundleStringData) == 0x18);

    // members
    std::uint8_t pad10[0x30 - 0x10];                                // 10
    hkArray<AnimationBundleStringData> animationBundleNameData;     // 30
    hkArray<AnimationBundleStringData> animationBundleFilenameData; // 40
};
static_assert(offsetof(hkbCharacterStringData, animationBundleNameData) == 0x30);
static_assert(offsetof(hkbCharacterStringData, animationBundleFilenameData) == 0x40);
} // namespace RE
