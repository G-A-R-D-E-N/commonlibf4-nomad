# commonlibf4-nomad code notes

Addresses are RVAs read from the OG 1.10.163, NG 1.10.984 and AE 1.11.240 executables. All of this is static reading; nothing was run in game.

## `include/RE/IDs.h:BSXAudio2Audio::Singleton`

Read from the unpacked executables, source:E:/RE-work/Tools/steamless-work (applies to every note here).

For `BSXAudio2Audio::Singleton`, the slot 1 function of the `BSXAudio2Audio` vtable (function at OG `0x1af14d0`, NG `0x152c7b0`, AE `0x1646df0`, source:E:/RE-work/Tools/steamless-work) stores the instance in id 1345596 on OG and 2703146 on NG and AE. The neighbouring slot holds the inner object's +0x48 pointer, which is OG id 1565436. NG and AE id 2703127 is a different global written elsewhere in that function.

## `include/RE/IDs.h:Workshop::ToggleEditMode`

OG has 9 direct call sites and 2195138 has 9 on both NG and AE. 2195130 has none, which is why it was rejected.

2195130 does take an argument, but never reads through it. It saves rcx in rdi (NG `0x340cea`, AE `0x39542a`) and only restores it to rcx before each tail jump to 2195127 (first site NG `0x340dcb`, AE `0x39550b`). 2195127 keeps it in rbx, tests it for null and tests a flag at `[rbx+0x40]` (NG `0x33ffd6`, AE `0x394716`). So "takes no args" is wrong, and so is treating 2195130 as using a `this`. source:E:/RE-work/Tools/steamless-work

## `include/RE/IDs_VTABLE.h:VTABLE::CombatMagicCasterLight`

Each row was compared with the exact RTTI class name at that id's address, source:E:/RE-work/Tools/steamless-work. `CombatMagicCasterLight` (501547) and `CombatInventoryItemMagicT_CombatInventoryItemStaff_CombatMagicCasterDisarm_` (59966) are right on all three runtimes.

The `BSTDerivedCreator` rows that reuse those two ids are wrong: `…Potion_CombatMagicCasterCloak…` has 501547 and `…Scroll_CombatMagicCasterLight…` has 59966. Their OG ids are 450949 and 582901. Their vtables exist on NG and AE but have no Address Library id there, so no single id can be right.

This is table-wide and not fixed here: 1,468 rows name the wrong class on at least one runtime (OG 1,265, NG 1,356, AE 1,468), and 24 of them are used by code, such as `TESCameraState` and `NiProperty`. Rows whose class name was not found in a runtime's RTTI were not checked on that runtime.

## `include/RE/M/MessageBoxData.h:MessageBoxData`

The real size is 0x68 on NG (sized free at `0xff38c5`) and 0x70 on AE (sized free at `0x107ad15`). OG frees it unsized, so its size was not read directly, but its message box code has no read of the AE fields.

AE's constructor (around `0x107ab59`) stores the cancel index at +0x68 and `index != -1` at +0x6C. The struct uses AE's larger size. `cancelButtonIndex` and `hasCancelButton` must not be read from a game-allocated object on OG or NG. Plugins should not allocate this type themselves: NG frees it with a size of 0x68, which does not match a `sizeof` allocation there. Use `MessageMenuManager::Create`.

## `include/RE/M/MessageBoxMenu.h:MessageBoxMenu`

The real size is 0xF0 on OG (allocation at `0x12af827`) and NG (sized free at `0xff3983`), and 0x100 on AE (sized free at `0x107add3`). AE inserts members, so the current message moves:

| Offset | OG and NG | AE |
| --- | --- | --- |
| 0xE8 | current message | has-cancel flag |
| 0xF0 | end of object | current message |
| 0xF8 | end of object | cancel button index |

The AE reader at `0x107a1ae` and the AE constructor at `0x1079710` show this. `GetCurrentMessage` replaces the old `currentMessage` member because no single member offset is right on all three runtimes.

## `include/RE/M/MessageMenuManager.h:MessageMenuManager::Create`

AE's `Create` reads one more stack argument than NG (`[rbp+0x90]` at `0x1078ee9`) and passes it on to the `MessageBoxData` constructor. AE's own callers pass -1 for no cancel button (for example `0x5bd27d`). Without it, the wrapper left that slot as stack garbage on AE, which could make the menu treat a button as a cancel button.

OG and NG do not read the extra slot. The x64 caller owns that stack space, so always passing it is harmless there.
