#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkRefPtr.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkaAnnotationTrack.h"
#include "RE/IDs_RTTI.h"
#include "RE/IDs_VTABLE.h"

namespace RE
{
class hkaAnimatedReferenceFrame;

class __declspec(novtable) hkaAnimation : public hkReferencedObject
{
  public:
    static constexpr auto RTTI{RTTI::hkaAnimation};
    static constexpr auto VTABLE{VTABLE::hkaAnimation};

    enum class AnimationType : std::int32_t
    {
        kUnknown = 0,
        kInterleaved = 1,
        kMirrored = 4,
        kSpline = 5,
        kQuantized = 6,
        kPredictive = 7
    };

    // members
    AnimationType type;                                  // 10
    float duration;                                      // 14
    std::int32_t numberOfTransformTracks;                // 18
    std::int32_t numberOfFloatTracks;                    // 1C
    hkRefPtr<hkaAnimatedReferenceFrame> extractedMotion; // 20
    hkArrayBase<hkaAnnotationTrack> annotationTracks;    // 28
};
static_assert(offsetof(hkaAnimation, duration) == 0x14);
static_assert(offsetof(hkaAnimation, annotationTracks) == 0x28);
} // namespace RE
