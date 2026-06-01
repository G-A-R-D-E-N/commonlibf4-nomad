#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkStringPtr.h"

namespace RE
{
class hkaAnnotationTrack
{
  public:
    struct Annotation
    {
        float time;          // 00
        std::uint32_t pad04; // 04
        hkStringPtr text;    // 08
    };
    static_assert(sizeof(Annotation) == 0x10);

    // members
    hkStringPtr trackName;               // 00
    hkArrayBase<Annotation> annotations; // 08
};
static_assert(sizeof(hkaAnnotationTrack) == 0x18);
} // namespace RE
