#pragma once

#include "RE/B/BSResource_ErrorCode.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/M/MemoryManager.h"

namespace RE::BSResource
{
class AsyncStream;
class Info;
class Location;
class Stream;

class __declspec(novtable) LocationTraverser
{
  public:
    static constexpr auto RTTI{RTTI::BSResource__LocationTraverser};
    static constexpr auto VTABLE{VTABLE::BSResource__LocationTraverser};

    virtual ~LocationTraverser() = default;                                 // 00
    virtual void ProcessName(const char *a_name, Location &a_location) = 0; // 01

    void operator()(const char *a_name, Location &a_location)
    {
        ProcessName(a_name, a_location);
    }
};
static_assert(sizeof(LocationTraverser) == 0x8);

class __declspec(novtable) Location
{
  public:
    static constexpr auto RTTI{RTTI::BSResource__Location};
    static constexpr auto VTABLE{VTABLE::BSResource__Location};

    virtual ~Location()
    {
    } // 00

    // add
    virtual ErrorCode DoMount()
    {
        return ErrorCode::kNone;
    } // 01
    virtual void DoUnmount()
    {
        return;
    } // 02
    virtual ErrorCode DoCreateStream(const char *a_path, BSTSmartPointer<Stream> &a_result, Location *&a_location,
                                     bool a_writable, LocationTraverser *a_traverser) = 0; // 03
    virtual ErrorCode DoCreateAsyncStream([[maybe_unused]] const char *a_path,
                                          [[maybe_unused]] BSTSmartPointer<AsyncStream> &a_result,
                                          [[maybe_unused]] Location *&a_location, [[maybe_unused]] bool a_writable,
                                          [[maybe_unused]] LocationTraverser *a_traverser)
    {
        return ErrorCode::kUnsupported;
    }                                                                                             // 04
    virtual ErrorCode DoTraversePrefix(char const *a_prefix, LocationTraverser &a_traverser) = 0; // 05
    virtual ErrorCode DoGetInfo([[maybe_unused]] char const *a_path, [[maybe_unused]] Info &a_result,
                                [[maybe_unused]] LocationTraverser *a_traverser)
    {
        return ErrorCode::kUnsupported;
    } // 07
    virtual ErrorCode DoGetInfo([[maybe_unused]] char const *a_path, [[maybe_unused]] Info &a_result,
                                [[maybe_unused]] Location *&a_location)
    {
        return ErrorCode::kUnsupported;
    } // 06
    virtual ErrorCode DoDelete([[maybe_unused]] char const *a_path)
    {
        return ErrorCode::kUnsupported;
    } // 08
    [[nodiscard]] virtual char const *DoGetName() const
    {
        return nullptr;
    } // 09
    [[nodiscard]] virtual std::uint32_t DoQBufferHint() const
    {
        return 0x10000;
    } // 0A
    [[nodiscard]] virtual std::uint32_t DoGetMinimumAsyncPacketSize() const
    {
        return 0x10000;
    } // 0B

    F4_HEAP_REDEFINE_NEW(Location);

    // members
    bool mounted; // 08
};
static_assert(sizeof(Location) == 0x10);
} // namespace RE::BSResource
