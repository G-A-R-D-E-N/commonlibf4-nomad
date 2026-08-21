#pragma once

namespace RE
{
class BSFaceGenAnimationData
{
  public:
    static constexpr auto RTTI{RTTI::BSFaceGenAnimationData};
    static constexpr auto VTABLE{VTABLE::BSFaceGenAnimationData};
    static constexpr auto Ni_RTTI{Ni_RTTI::BSFaceGenAnimationData};

    enum class Morph : std::uint32_t
    {
        kBrowSqueeze = 0x0,
        kJawFwd = 0x1,
        kJawOpen = 0x2,
        kLBrowOutUp = 0x3,
        kLCheekUp = 0x4,
        kLFrown = 0x5,
        kLJaw = 0x6,
        kLLipCornerIn = 0x7,
        kLLipCornerOut = 0x8,
        kLLwrLidDn = 0x9,
        kLLwrLidUp = 0xA,
        kLLwrLipDn = 0xB,
        kLLwrLipUp = 0xC,
        kLMidBrowDn = 0xD,
        kLMidBrowUp = 0xE,
        kLNoseUp = 0xF,
        kLOutBrowDn = 0x10,
        kLSmile = 0x11,
        kLUprLidDn = 0x12,
        kLUprLidUp = 0x13,
        kLUprLipDn = 0x14,
        kLUprLipUp = 0x15,
        kLwrLipFunnel = 0x16,
        kLwrLipRollIn = 0x17,
        kLwrLipRollOut = 0x18,
        kPucker = 0x19,
        kRBrowOutUp = 0x1A,
        kRCheekUp = 0x1B,
        kRFrown = 0x1C,
        kRJaw = 0x1D,
        kRLipCornerIn = 0x1E,
        kRLipCornerOut = 0x1F,
        kRLwrLidDn = 0x20,
        kRLwrLidUp = 0x21,
        kRLwrLipDn = 0x22,
        kRLwrLipUp = 0x23,
        kRMidBrowDn = 0x24,
        kRMidBrowUp = 0x25,
        kRNoseUp = 0x26,
        kROutBrowDn = 0x27,
        kRSmile = 0x28,
        kRUprLidDn = 0x29,
        kRUprLidUp = 0x2A,
        kRUprLipDn = 0x2B,
        kRUprLipUp = 0x2C,
        kStickyLips = 0x2D,
        kUprLipFunnel = 0x2E,
        kUprLipRollIn = 0x2F,
        kUprLipRollOut = 0x30,
        kTongue = 0x31,
        kLookUp = 0x32,
        kLookDown = 0x33,
        kLookLeft = 0x34,
        kLookRight = 0x35,
        kTotal = 0x36
    };

    static constexpr std::uint32_t MORPH_COUNT{54};
    static constexpr std::uint32_t CURRENT_MORPHS_OFFSET{0xF0};
    static constexpr float MIN_MORPH_VALUE{0.0F};
    static constexpr float MAX_MORPH_VALUE{1.0F};

    [[nodiscard]] static constexpr float ClampMorph(float a_value) noexcept
    {
        if (a_value < MIN_MORPH_VALUE)
        {
            return MIN_MORPH_VALUE;
        }

        if (a_value > MAX_MORPH_VALUE)
        {
            return MAX_MORPH_VALUE;
        }

        return a_value;
    }

    [[nodiscard]] static constexpr float PercentToMorph(float a_percent) noexcept
    {
        return ClampMorph(a_percent * 0.01F);
    }

    [[nodiscard]] float GetMorph(Morph a_morph) const noexcept
    {
        return currentMorphs[static_cast<std::uint32_t>(a_morph)];
    }

    void SetMorph(Morph a_morph, float a_value) noexcept
    {
        currentMorphs[static_cast<std::uint32_t>(a_morph)] = ClampMorph(a_value);
    }

    void SetMorphPercent(Morph a_morph, float a_percent) noexcept
    {
        SetMorph(a_morph, PercentToMorph(a_percent));
    }

    // members
    std::byte pad000[0x0F0];          // 000
    float currentMorphs[MORPH_COUNT]; // 0F0
};
static_assert(offsetof(BSFaceGenAnimationData, currentMorphs) == BSFaceGenAnimationData::CURRENT_MORPHS_OFFSET);
static_assert(sizeof(BSFaceGenAnimationData::currentMorphs) == 0xD8);
static_assert(static_cast<std::uint32_t>(BSFaceGenAnimationData::Morph::kTotal) == BSFaceGenAnimationData::MORPH_COUNT);
} // namespace RE
