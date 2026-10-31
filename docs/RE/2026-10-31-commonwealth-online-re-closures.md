# Commonwealth Online #407: RE closures, 2026-10-31

Answers for [GARDEN/CommonwealthOnline-Matrix#407](https://git.nomadicinteractive.dev/GARDEN/CommonwealthOnline-Matrix/issues/407).
Runtimes: Fallout 4 OG 1.10.163, NG 1.10.984, AE 1.11.240. Static unless stated; the only runtime
value in here is noted as such. Raw evidence, re-runnable scripts and per-row transcripts are in the
research repository: `ReverseEng/Fallout4_Runtime_Research` branch `re/co407-2026-10-31-open-items`,
directory `RE-Work/subsystems/commonwealth-online-re/co407-2026-10-31-open-items/`
([PR #163](https://re.nomadicinteractive.dev/ReverseEng/Fallout4_Runtime_Research/pulls/163)).

Method: disassembly and decompilation of the unpacked retail images, plus the Microsoft debug symbol
data supplied for an earlier retail build (used for names and class layout only; its addresses are
never used as game addresses).

## 1. `CommandExecuteDispatch` (item 553-5) - closed: the object does not exist

- The global read at the dispatch site is `Console::pVMBridge` (OG `0x5ADB410`, NG `0x306FE30`,
  AE `0x33127B0`; per-build address-library ids OG `749385`, NG/AE `2701385`).
- `Console::VMBridge` is an **abstract interface**: its vtable has five slots and every one is
  `_purecall`; `Console::SetVMBridge` has **zero callers**; no class in any shipped image derives from
  it (no RTTI base entry references its type descriptor).
- The class is only present in the beta executable; the retail images do not contain its RTTI at all.
- Store scans for the global: **0 hits** in 1.10.163, 1.10.984, 1.11.240 and the retail beta-era
  build; the only references are four reads per build.
- **Runtime measurement** (AE 1.11.240, installed game, no build made): polling
  `Fallout4.exe+0x33127B0` from a live process every 400-500 ms for 200 s and again for 330 s returned
  `0x0000000000000000` on every sample. With a null pointer the guarded `call [rax+0x20]` never runs.
- Conclusion: there is no concrete class to report; the probe row should be dropped (or kept as a
  tripwire). `CreateRef` was already refuted: the call is the interface's fourth virtual slot, not a
  factory.

## 2. BSAnimationGraphChannel binding - `RegisterChannels`, and it replaces

- Real names: `BSAnimationGraphManager::RegisterChannels(const BSScrapArray<BSTSmartPointer<BSAnimationGraphChannel>>&)`
  -> `RegisterChannelsHelper<BSScrapArrayAllocator>(...)`. `BindChannels` does not exist.
- Per build: `RegisterChannels` OG `0x1608550` / NG `0x11F4650` / AE `0x130ECC0`; helper OG
  `0x160A6A0` / NG `0x11F6620` / AE `0x1310C90`; `InitializeGraphManager` OG `0x81D4E0` /
  NG `0x7C5730` / AE `0x8191C0`.
- **Replace semantics**: on a name hit the old element is removed (`MoveItems` + size--), its array
  reference released and the deleting destructor called at zero, then the new channel is appended.
  Exactly one element per name survives. `RegisterChannels` passes the out-array as null, so a second
  bind releases the old channel and then calls `Reset()` (slot 2) on every bound channel.
- All channel types go to `+0x10` (`boundChannel`); `+0x28` is `bumpedChannel` (never written by
  binding), `+0x40` is a name-key gate table, `+0x58` is destructor-only.
- Manager destructor (all builds) walks four arrays `+0x10/+0x28/+0x40/+0x58` with locked decrements
  and deletes at zero.
- Open: who populates the `+0x40` gate table (`Load` `0x1608F50`, `SetActiveGraph` `0x1608880`,
  `PushBoundChannels` `0x1609640` are the candidates, none decompiled).

## 3. Scaleform `ExternalImage` (tag 1009) file resolution - closed

- The tag loader does no I/O: it builds a `GFx::ImageFileInfo` (`+0x20` = **second** `str8` = file
  name) and registers it by CharacterId (`LoadProcess::AddDataResource`).
- Resolution is lazy on first bind: `ImageFileResourceCreator::CreateResource` ->
  `ImageResource::CreateImageFileKey` / `GetFileURL` -> `ImageCreator::LoadExportedImage` ->
  `LoadImageFile` (retries with `.dds` if the name has no `.dds` extension) ->
  `BSScaleformFileOpener::OpenFile` -> `OpenFileEx` -> `BSResource::ID` +
  `BSResource::EntryDB<BSResource::ScaleformFile::DBTraits>`.
- So the `.dds` may be loose or inside a BA2; the normal archive-before-loose precedence applies.
- Per build `BSScaleformFileOpener` vtable / `OpenFile` / `OpenFileEx`: OG `0x2EB9710` /
  `0x21146B0` / `0x2114720`; NG `0x25135F0` / `0x1A02A30` / `0x1A02AA0`; AE `0x2728DB8` /
  `0x1B1E360` / `0x1B1E3D0`.

## 4. Archive and script precedence - closed

- `GlobalLocations` keeps a list sorted ascending by priority; traversal is head-first and stops at
  the first success, so a **higher priority number means lower precedence**.
- Archives register at priority `0`, loose directories at `0x100` -> **archives beat loose files**,
  including for Papyrus scripts.
- Equal priority is LIFO: the insert stops at the first node with `priority >= new`, so the last
  registered location is visited first.
- The script store proves the script path: `GameScript::Store::Open` calls
  `BSResource::GetOrCreateStream` (per build OG `0x1B7D440`, NG `0x158D9E0`, AE `0x16A88D0`);
  script-side functions: OG `0x1358130`, NG `0x10570CC`, AE `0x10DCFFC`.
- Read-only opens resolve through the merged `Archive2::Index`: one entry per 12-byte resource ID,
  and a later insert overwrites the earlier one in place (the loser is not kept). `dataFileIndex` only
  names the data file, it does not arbitrate.
- Name hash: reflected CRC-32 (poly `0xEDB88320`, init 0, xorout 0); directory hash excludes the
  trailing separator; extension is the first four characters packed little-endian. The table index is
  sign-extended, so a byte `>= 0x80` fetches an entry before the normaliser table (all zero) and
  **ends hashing** - names differing after such a byte collide.
- `bInvalidateOlderFiles` only changes which loose prefixes are registered, not the rank.

## 5. 568 Q3a - `+0xC8` is yaw, `+0xC0` is pitch

- `Projectile::ComputeCastInfo` (OG `0xFD7090`, NG `0xDCB680`, AE `0xE51790`) calls
  `NiMatrix3::FromEulerAnglesZYX(Z=[+0xC8], Y=0, X=[+0xC0])`; the argument order is fixed by
  `TESObjectREFR::GetOrientation`, which calls `FromEulerAnglesXYZ` with `(+0xC0,+0xC4,+0xC8)` and
  `FromEulerAnglesZXY` with `(+0xC8,+0xC0,+0xC4)`.
- Related names: `Projectile::SetOriginAndDirection` OG `0xFCADA0`, `Projectile::InitializeFromLaunch`
  OG `0xFD33F0`, `Projectile::RunTargetPick` OG `0xFCF860`, `BeamProjectile::RunTargetPick`
  NG `0xD99760` / AE `0xE1F7B0`, `TESObjectWEAP::Fire` NG `0x425860` / AE `0x4799B0`.
- Open: 568 Q3b, Q3c, Q1b, Q2b, Q2c.

## 6. Probe rows (PR #553) - answered, with two corrections

- `553-4`: OG owner `BSAnimationGraphManager::Update` (symbol data `0x16080C0` -> OG `0x16080D0`, **275 bytes**
  - the 1751 figure was decompile-text length); `rax` = `??_7Actor@@6BIPostAnimationChannelUpdateFunctor@@@`
  (the Actor sub-object at `actor+0x168`); callee slot 1 = `Actor::DoPostAnimationChannelUpdate`
  OG `0xDC44F0`, which tail-calls `AIProcess::RunQueuedAnimationActionAndAdjustments` `0xE39370`.
- `553-6`: **refuted** - NG `0xAB6130` never reads `[rcx]`; 4-argument forwarder to `0x3D7C40`.
- `553-9`/`R3`: `xmm1` is the volume float, consumer `BGSSoundCategory::SetCategoryVolume(float)`
  OG `0x4BD5F0`; the `rdx` "curved label" is **not a parameter** (it is overwritten before any read).
- `553-11`: all 21 `kSites` rows match their own images (21/21, 0 mismatches), including the 10 that
  had no second source. The table has 21 rows, not 18.
- `R1`: probe 2 OG `0xCD8720` is `BGSSaveLoadChangesMap::SetChanges(uint, BGSFormChanges const&)`,
  **not** a cell-unload insert; OG `0x4E29B0` is `Script::CompileAndRun`.
- `PH.1-PH.3`: three real 5-byte-form hazards, all on probe 5 (OG `0x160815F`, NG `0x11F40F2`,
  AE `0x130E762` - the null-guard branch lands inside the overwritten bytes); use the 14-byte form
  there. AE `0xC3B000+12` needs the 5-byte form. No jump-table or function-pointer entry lands in any
  span.

## 7. BA2 hash verification sweep

- GNRL archives: **465,486 of 465,489 records verified** (dir, name and extension hashes), 3 mismatches
  in one archive; the convention is: per archive, a `u32` count then per-file `u16` length + string.
- DX10 texture archives: the same hash formula reproduces sampled entries (e.g. 1,055 of 3,551
  in-place matches on `Fallout4 - Textures1.ba2`, and spot checks on other archives), but the DX10
  record array does not align with the name table the way GNRL does (name index and record index
  differ, and the record array extends past the header's file count), so a full per-record sweep needs
  the DX10 record layout decoded. This is the only open part of the sweep.

## 8. What is still open

| Row | State | Next step |
| --- | --- | --- |
| MOV-1 on-foot/vertibird chain | OG proven (MOVT SPED path, run 350.87 / sprint 500, PA 311.66/497.06, gravity = g x 69.99125, vertibird 800/1000, `moveto` single-call) | map the OG anchors to NG/AE |
| MOV-1 terminal velocity | no clamp exists in the character controller; it is gravity-vs-damping equilibrium | needs a measured fall or the damping coefficient |
| MOV-1 rider per-frame position | `MountInteraction::SyncWithMount` drives the rider, not a per-frame vehicle-to-player copy | read `SyncWithMount` call order |
| 568 Q3b/Q3c/Q1b/Q2b/Q2c | open | decode `InitializeFromLaunch`/`Launch`, `AdjustAttackDamage`, `Fire`'s ammo uses |
| Canonical subrecord order, non-WEAP types | loader frame mapped (TESForm vtable slot 9) for 58 classes per build; WEAP proven order-insensitive | classify the 25+ located loader bodies |
| Prisma VR ids | flat-side anchors proven; VR matching not run | run the masked-sequence matcher against the VR image |
| DX10 BA2 sweep | partial as above | decode the DX10 record array layout |

Nothing in this document was inferred where a symbol, address or measurement is cited. All values are
static unless the row says runtime.
