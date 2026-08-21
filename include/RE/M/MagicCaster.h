#pragma once

namespace RE
{
class Actor;
class MagicItem;
class TESObjectREFR;

class MagicCaster
{
  public:
    void CastSpellImmediate(MagicItem *a_spell, bool a_arg2, TESObjectREFR *a_target, float a_effectiveness,
                            bool a_arg5, float a_arg6, Actor *a_actor)
    {
        using func_t = decltype(&MagicCaster::CastSpellImmediate);
        static REL::Relocation<func_t> func{ID::MagicCaster::CastSpellImmediate};
        return func(this, a_spell, a_arg2, a_target, a_effectiveness, a_arg5, a_arg6, a_actor);
    }

    void InterruptCast(bool a_arg)
    {
        using func_t = decltype(&MagicCaster::InterruptCast);
        static REL::Relocation<func_t> func{ID::MagicCaster::InterruptCast};
        return func(this, a_arg);
    }
};
} // namespace RE
