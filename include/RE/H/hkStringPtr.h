#pragma once

namespace RE
{
class hkStringPtr
{
  public:
    [[nodiscard]] const char *c_str() const noexcept
    {
        return reinterpret_cast<const char *>(reinterpret_cast<std::uintptr_t>(data) & ~static_cast<std::uintptr_t>(1));
    }

    [[nodiscard]] const char *get() const noexcept
    {
        return c_str();
    }

    operator const char *() const noexcept
    {
        return get();
    }

    // members
    const char *data; // 00
};
static_assert(sizeof(hkStringPtr) == 0x08);
} // namespace RE
