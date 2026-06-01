#pragma once

namespace RE
{
class hkbNode;

struct hkbNodeInfo
{
    // members
    std::uint64_t unk00; // 00
    hkbNode *nodeClone;  // 08
};
static_assert(offsetof(hkbNodeInfo, nodeClone) == 0x08);
} // namespace RE
