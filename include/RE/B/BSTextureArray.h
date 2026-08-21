#pragma once

#include "RE/B/BSResource_ID.h"
#include "RE/B/BSTArray.h"
#include "RE/N/NiPointer.h"
#include "RE/N/NiTexture.h"

namespace RE::BSTextureArray
{
class __declspec(novtable) StaticTexture : public NiTexture // 00
{
  public:
    static constexpr auto RTTI{RTTI::BSTextureArray__StaticTexture};
    static constexpr auto VTABLE{VTABLE::BSTextureArray__StaticTexture};

    struct LoadDesc
    {
        BSResource::ID id;        // 00
        std::uint32_t sliceIndex; // 0C
        std::uint32_t priority;   // 10
        bool accepted;            // 14
        std::byte pad15[3];       // 15
    };
    static_assert(sizeof(LoadDesc) == 0x18);

    // Engine constructors are omitted because their OG and AE signatures differ.
    [[nodiscard]] std::uint32_t GetSliceCount() const noexcept
    {
        return sliceCount;
    }

    std::uint32_t LoadSlices(LoadDesc *a_descriptors, std::uint32_t a_count)
    {
        using func_t = decltype(&StaticTexture::LoadSlices);
        static REL::Relocation<func_t> func{ID::BSTextureArray::StaticTexture::LoadSlices};
        return func(this, a_descriptors, a_count);
    }

    std::uint32_t StartLoadSlices(LoadDesc *a_descriptors, std::uint32_t a_count)
    {
        constexpr std::size_t vtableIndex = 0x29;
        const auto vtable = *reinterpret_cast<const std::uintptr_t *const *>(this);

        if (REX::FModule::IsRuntimeOG())
        {
            using func_t = std::uint32_t (*)(StaticTexture *, LoadDesc *, std::uint32_t);
            const auto func = reinterpret_cast<func_t>(vtable[vtableIndex]);
            return func(this, a_descriptors, a_count);
        }

        if (REX::FModule::IsRuntimeAE())
        {
            using func_t = std::uint32_t (*)(StaticTexture *, LoadDesc *, std::uint32_t, std::uint32_t);
            const auto func = reinterpret_cast<func_t>(vtable[vtableIndex]);
            return func(this, a_descriptors, a_count, a_count);
        }

        REX::FAIL("BSTextureArray::StaticTexture::StartLoadSlices is unsupported on this runtime");
        return 0;
    }

    [[nodiscard]] bool PollLoadSlices() const
    {
        using func_t = decltype(&StaticTexture::PollLoadSlices);
        static REL::Relocation<func_t> func{ID::BSTextureArray::StaticTexture::PollLoadSlices};
        return func(this);
    }

    void WaitLoadSlices() const
    {
        using func_t = decltype(&StaticTexture::WaitLoadSlices);
        static REL::Relocation<func_t> func{ID::BSTextureArray::StaticTexture::WaitLoadSlices};
        return func(this);
    }

  protected:
    bool LoadSliceFromDesc(LoadDesc &a_descriptor)
    {
        using func_t = decltype(&StaticTexture::LoadSliceFromDesc);
        static REL::Relocation<func_t> func{ID::BSTextureArray::StaticTexture::LoadSliceFromDesc};
        return func(this, a_descriptor);
    }

  public:
    // members
    std::uint32_t sliceCount;            // 48
    std::uint32_t mipCount;              // 4C
    std::uint32_t totalRequestCount;     // 50
    volatile std::uint32_t streamedDone; // 54
    std::uint32_t synchronousDone;       // 58
    std::uint32_t notAcceptedCount;      // 5C
};
static_assert(sizeof(StaticTexture) == 0x60);

class __declspec(novtable) StaticTextureIndexed : public StaticTexture // 00
{
  public:
    static constexpr auto RTTI{RTTI::BSTextureArray__StaticTextureIndexed};
    static constexpr auto VTABLE{VTABLE::BSTextureArray__StaticTextureIndexed};

    [[nodiscard]] static NiPointer<StaticTextureIndexed> Create(std::uint32_t a_sliceCount,
                                                                std::uint32_t a_sliceIDCount, std::uint32_t a_mipCount,
                                                                bool a_sRGB)
    {
        const auto isOG = REX::FModule::IsRuntimeOG();
        const auto isAE = REX::FModule::IsRuntimeAE();
        if (!isOG && !isAE)
        {
            REX::FAIL("BSTextureArray::StaticTextureIndexed::Create is unsupported on this runtime");
            return {};
        }
        if (isOG && a_sliceCount != a_sliceIDCount)
        {
            REX::FAIL("BSTextureArray::StaticTextureIndexed cannot use a separate slice ID count on OG");
            return {};
        }

        // The engine constructor initializes NiObject, so invoke it on raw storage.
        auto *object = RE::malloc<StaticTextureIndexed>();
        if (!object)
        {
            REX::FAIL("out of memory");
            return {};
        }

        if (isOG)
        {
            using func_t = StaticTextureIndexed *(*)(StaticTextureIndexed *, std::uint32_t, std::uint32_t, bool);
            static REL::Relocation<func_t> func{ID::BSTextureArray::StaticTextureIndexed::ctor};
            return NiPointer<StaticTextureIndexed>{func(object, a_sliceCount, a_mipCount, a_sRGB)};
        }

        using func_t =
            StaticTextureIndexed *(*)(StaticTextureIndexed *, std::uint32_t, std::uint32_t, std::uint32_t, bool);
        static REL::Relocation<func_t> func{ID::BSTextureArray::StaticTextureIndexed::ctor};
        return NiPointer<StaticTextureIndexed>{func(object, a_sliceCount, a_sliceIDCount, a_mipCount, a_sRGB)};
    }

    [[nodiscard]] static NiPointer<StaticTextureIndexed> Create(std::uint32_t a_sliceCount, std::uint32_t a_mipCount,
                                                                bool a_sRGB)
    {
        return Create(a_sliceCount, a_sliceCount, a_mipCount, a_sRGB);
    }

    void CopyFrom(StaticTextureIndexed *a_source, bool a_copySliceIDs)
    {
        using func_t = decltype(&StaticTextureIndexed::CopyFrom);
        static REL::Relocation<func_t> func{ID::BSTextureArray::StaticTextureIndexed::CopyFrom};
        return func(this, a_source, a_copySliceIDs);
    }

    [[nodiscard]] std::uint32_t FindSlice(const BSResource::ID &a_id) const
    {
        using func_t = decltype(&StaticTextureIndexed::FindSlice);
        static REL::Relocation<func_t> func{ID::BSTextureArray::StaticTextureIndexed::FindSlice};
        return func(this, a_id);
    }

    [[nodiscard]] const BSResource::ID &GetSliceID(std::uint32_t a_index) const noexcept
    {
        return sliceIDs[a_index];
    }

    // members
    BSTArray<BSResource::ID> sliceIDs; // 60
};
static_assert(sizeof(StaticTextureIndexed) == 0x78);
} // namespace RE::BSTextureArray
