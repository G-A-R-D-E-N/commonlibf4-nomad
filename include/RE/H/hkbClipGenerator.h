#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkQsTransform.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkStringPtr.h"
#include "RE/H/hkaAnimation.h"
#include "RE/H/hkaAnimationControl.h"
#include "RE/H/hkbGenerator.h"
#include "RE/IDs_RTTI.h"
#include "RE/IDs_VTABLE.h"

namespace RE
{
class hkaDefaultAnimationControlMapperData;
class hkbClipTriggerArray;
struct hkbContext;

class __declspec(novtable) hkbClipGenerator : public hkbGenerator
{
  public:
    static constexpr auto RTTI{RTTI::hkbClipGenerator};
    static constexpr auto VTABLE{VTABLE::hkbClipGenerator};

    enum class PlaybackMode : std::uint8_t
    {
        kSinglePlay = 0,
        kLooping = 1,
        kUserControlled = 2,
        kPingPong = 3,
        kCount = 4
    };

    // members
    std::uint8_t pad10[0x38 - 0x10];                       // 10
    hkStringPtr name;                                      // 38
    std::uint8_t pad40[0x50 - 0x40];                       // 40
    std::uint8_t generatorPartitionInfo[0x28];             // 50
    std::uint8_t pad78[0x88 - 0x78];                       // 78
    hkStringPtr unk88;                                     // 88
    hkStringPtr animationName;                             // 90
    hkRefPtr<hkbClipTriggerArray> triggers;                // 98
    std::uint8_t padA0[0x04];                              // A0
    float cropStartAmountLocalTime;                        // A4
    float cropEndAmountLocalTime;                          // A8
    float startTime;                                       // AC
    float playbackSpeed;                                   // B0
    float enforcedDuration;                                // B4
    float userControlledTimeFraction;                      // B8
    std::uint16_t animationBindingIndex;                   // BC
    PlaybackMode mode;                                     // BE
    std::uint8_t flags;                                    // BF
    std::uint8_t padC0[0x10];                              // C0
    hkRefPtr<hkaDefaultAnimationControl> animationControl; // D0
    hkRefPtr<hkbClipTriggerArray> originalTriggers;        // D8
    hkaDefaultAnimationControlMapperData *mapperData;      // E0
    hkaAnimationBinding *binding;                          // E8
    std::uint8_t padF0[0x10];                              // F0
    hkQsTransform extractedMotion;                         // 100
    std::uint8_t pad130[0x08];                             // 130
    std::uint8_t pad138[0x08];                             // 138
    float localTime;                                       // 140
    float time;                                            // 144
    float previousUserControlledTimeFraction;              // 148
    std::uint8_t pad14C[0x04];                             // 14C
    bool resetLocalTime;                                   // 150
    bool hasSetLocalTime;                                  // 151
    bool atEnd;                                            // 152
    bool ignoreStartTime;                                  // 153

    [[nodiscard]] const char *GetClipName() const
    {
        return animationName.get();
    }
};
static_assert(offsetof(hkbClipGenerator, name) == 0x38);
static_assert(offsetof(hkbClipGenerator, animationName) == 0x90);
static_assert(offsetof(hkbClipGenerator, triggers) == 0x98);
static_assert(offsetof(hkbClipGenerator, cropStartAmountLocalTime) == 0xA4);
static_assert(offsetof(hkbClipGenerator, playbackSpeed) == 0xB0);
static_assert(offsetof(hkbClipGenerator, animationBindingIndex) == 0xBC);
static_assert(offsetof(hkbClipGenerator, mode) == 0xBE);
static_assert(offsetof(hkbClipGenerator, flags) == 0xBF);
static_assert(offsetof(hkbClipGenerator, animationControl) == 0xD0);
static_assert(offsetof(hkbClipGenerator, binding) == 0xE8);
static_assert(offsetof(hkbClipGenerator, extractedMotion) == 0x100);
static_assert(offsetof(hkbClipGenerator, localTime) == 0x140);
static_assert(offsetof(hkbClipGenerator, hasSetLocalTime) == 0x151);
} // namespace RE
