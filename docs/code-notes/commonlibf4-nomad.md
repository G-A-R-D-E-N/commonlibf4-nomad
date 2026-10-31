# commonlibf4-nomad code notes

Addresses are RVAs read from the OG 1.10.163, NG 1.10.984 and AE 1.11.240 executables. All of this is static reading; nothing was run in game.

## `include/RE/B/BSXAudio2Audio.h:BSXAudio2Audio::GetSingleton`

Read from the unpacked executables, source:E:/RE-work/Tools/steamless-work (applies to every note here).

Slot 1 of the `BSXAudio2Audio` vtable (OG `0x1af14d0`, NG `0x152c7b0`, AE `0x1646df0`) stores the instance in id 1345596 on OG and 2703146 on NG and AE. The neighbouring slot holds the inner object's +0x48 pointer, which is OG id 1565436. NG and AE id 2703127 is a different global written elsewhere in that function.

The ids live in the header because this was the only user of the old `ID::BSXAudio2Audio::Singleton` row, and `IDs.h` is over the source line limit, so an edit there has to shrink the file. Removing the wrong row does that.

## `include/RE/IDs.h:Workshop::ToggleEditMode`

OG has 9 direct call sites and 2195138 has 9 on both NG and AE. 2195130 has none, which is why it was rejected. It does read its first argument, so the "takes no args" comment on this row is wrong; the id itself is right. The comment stays for now because the line limit blocks same-length edits to `IDs.h`.

## `include/RE/M/MessageBoxData.h:MessageBoxData`

The real size is 0x68 on NG (sized free at `0xff38c5`) and 0x70 on AE (sized free at `0x107ad15`). OG frees it unsized, so its size was not read directly, but its message box code has no read of the AE fields.

AE's constructor (around `0x107ab59`) stores the cancel index at +0x68 and `index != -1` at +0x6C. The struct uses the larger size so that memory allocated from `sizeof` is large enough on every runtime. `cancelButtonIndex` and `hasCancelButton` must not be read from a game-allocated object on OG or NG.

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
