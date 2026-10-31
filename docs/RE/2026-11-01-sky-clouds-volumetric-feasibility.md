# Fallout 4 sky and cloud rendering — findings

Date: 2026-11-01. Scope: Fallout 4 **1.10.163 (OG)** primarily, **1.11.240 (AE)** where noted.

Status: **static reverse engineering only. Nothing here is runtime-verified; no offset has been
validated in game.** Treat every item as a hypothesis until confirmed on a live process.

Method: local RE corpus (Ghidra decompiles, call graph, RTTI→vtable→slot resolution, Address
Library), CommonLibF4 headers, and engine symbol/type data from an earlier Fallout 4 build (names,
class layouts and nested enums only — its addresses are not runtime addresses of either build and are
never used as hook offsets).

---

## 1. Where the sky is drawn

`BSShaderManager::ShaderEnum` is the render-batch slot order:

```
0 Effect, 1 Utility, 2 DistantTree, 3 Particle,
4 DFPrepass, 5 DFLight, 6 DFComposite,
7 SKY,
8 Lighting, 9 BloodSpatter, 10 Water, 11 FaceCustomization, 12 ImageSpace
```

`BSBatchRenderer` keeps `BSTArray<PassGroup> RenderPassA[13]` indexed by that enum.

Scene submission order, decompiled from
`BSShaderAccumulator::FinishAccumulating_Standard_PreResolveDepth` (OG `0x282DD00`):

```
RenderAllBatches()                     // OG 0x282EEF0: loops shader 0..12 in enum order
RenderGeometryGroup(9); (8); (0); (1)  // GG_LOW_ANISO, GG_NO_SHADOW, GG_LODLAND, GG_LODOBJECTS
RenderBatches(shader = 7 SKY, alpha = 0, allGroups)   // OG 0x287F380
RenderGeometryGroup(0xE)               // GG_SKYCLOUDS
FUN_14282e300()                        // further geometry groups (purpose unverified)
FUN_1428813D0(...)                     // alpha/transparent passes (calls PersistentPassList::AlphaSort)
```

So the sky sits after deferred G-buffer/lighting/composite and before forward lighting,
transparent passes and ImageSpace/post. Sky geometry is excluded from depth/shadow passes:
`BSSkyShaderProperty::GetRenderPasses` returns `nullptr` for render modes 13..17
(`kDepthPrepass … kShadowmapPB`).

Within one shader slot, pass groups are ordered by `uiPassEnum`
(`BSBatchRenderer::RenderBatchesInOrder`, OG `0x287F4E0`); because the sky pass enum is the technique
id, sky sub-passes draw in technique order 0→8.

## 2. Sky element model

`Sky` (`sizeof 0x480`) owns one object per element; it is not itself a scene node.

| Offset | Member | Notes |
|--------|--------|-------|
| `+0x008` | `NiPointer<BSMultiBoundNode> root` | sky scene-graph root |
| `+0x010`/`+0x018` | `moonsRoot` / `auroraRoot` | |
| `+0x040` | `TESClimate* currentClimate` | |
| `+0x048`/`0x050`/`0x058`/`0x060` | `currentWeather` / `lastWeather` / `defaultWeather` / `overrideWeather` | |
| `+0x070` | `Atmosphere*` | sky quad / horizon / fog |
| `+0x078` | `Stars*` | |
| `+0x080` | `Sun*` | sun billboard + `NiDirectionalLight`s |
| `+0x088` | `Clouds*` | cloud layer geometry |
| `+0x090`/`0x098` | `Moon* masser` / `secunda` | |
| `+0x0A0` | `Precipitation*` | |
| `+0x0A8` | `NiColor skyColor[19]` | weather color rows |
| `+0x31C..0x324` | `windSpeed` / `windAngle` / `windTurbulence` | |
| `+0x328..0x354` | `fogDistances[8]`, `fogHeight`, `fogPower`, `fogClamp`, `fogHighDensityScale` | |
| `+0x358`/`0x35C`/`0x360` | `currentGameHour` / `lastWeatherUpdate` / `currentWeatherPct` | |
| `+0x36C` | `Mode mode` (`kNone/kInterior/kSkyDomeOnly/kFull`) | |
| `+0x378` | `flash` | lightning |
| `+0x394` | `Flags flags` (`kHideSky` bit 7, `kUpdateWind` bit 20, …) | |

Every sky element derives from `SkyObject` (`sizeof 0x10`; virtual dtor, `GetRoot`, `Update(Sky*, float)`;
`spRoot NiNode* +0x08`).

| Class | sizeof | Geometry / key members |
|-------|--------|------------------------|
| `Clouds` | `0x518` | `spClouds[32] +0x10`; `hTransTexture[32] +0x110`; `spTransTexture[32] +0x210`; `pColors[32] +0x310`; `fAlpha[32] +0x490`; `usNumLayers +0x510`; `bForceUpdate +0x512`; `MAX_LAYERS = 32` |
| `Atmosphere` | `0x38` | `spAtmosphere BSTriShape +0x10`; `spFog BSFogProperty +0x18`; `spSkyQuadNode NiNode +0x20`; `spSkyQuad BSTriShape +0x28` |
| `Sun` | `0x58` | `spSunBaseNode +0x10`; `spSunGlareNode +0x18`; `spSunBase +0x20`; `spSunQuery +0x28`; `spSunGlare +0x30`; `spLight NiDirectionalLight +0x38`; `spCloudLight NiDirectionalLight +0x40`; `fGlareScale +0x48`; `spSunAccumulator +0x50` |
| `Moon` | `0xD8` | base/glare/shadow nodes + colors |
| `Stars` | `0x20` | star-dome geometry |
| `Precipitation` | `0xA0` | occlusion camera, rain direction |

## 3. How clouds are represented

WTHR record (`TESWeather`, `sizeof 0xFC8`) authors up to 32 independent 2D layers:

| Offset | Member |
|--------|--------|
| `+0x028` | `TESTexture1024 cloudTexture[32]` |
| `+0x228` | `int8 cloudLayerSpeedY[32]` |
| `+0x248` | `int8 cloudLayerSpeedX[32]` |
| `+0x268` | `uint32 cloudColorData[32][8]` |
| `+0x668` | `float cloudAlpha[32][8]` |
| `+0xA68` | `uint32 cloudLayerDisabledBits` |
| `+0xA6C` | `int8 weatherData[20]` (1 = kCloudSpeedY, 2 = kCloudSpeedX, 3 = kTransDelta, 0 = kWindSpeed) |
| `+0xAC8` | `uint32 colorData[19][8]` |
| `+0xDF0` | `uint32 numCloudLayers` |

Runtime: each layer is a `BSGeometry` (usually `BSTriShape`) carrying a `BSSkyShaderProperty`
(`sizeof 0xB0`):

| Offset | Member | Use |
|--------|--------|-----|
| `+0x70` | `NiColorA kBlendColor` | per-object color + alpha |
| `+0x80` | `NiPointer<NiTexture> textures[3]` | base / blend cloud textures |
| `+0x98` | `BSFixedString TextureFilename` | |
| `+0xA0` | `float fBlendValue` | layer blend |
| `+0xA4` | `uint16 usCloudLayer` | layer index 0..31 |
| `+0xA6` | `bool bFadeSecondTexture` | |
| `+0xA8` | `int skyObjectType` | `SO_SUN=0, SO_SUN_GLARE=1, SO_ATMOSPHERE=2, SO_CLOUDS=3, SO_SKYQUAD=4, SO_STARS=5, SO_MOON=6, SO_MOON_SHADOW=7, SO_OTHER=8` |

`BSSkyShader` (`sizeof 0x120`) statics: `pInstance`, `pSkyColor[3] NiColorA`, `fPlayerDepth`,
`fSunBrightness`, `fSkyBrightness`, `pLUMRamp[2]`, `pCloudTexCoordOffset[32] NiPoint2`,
`NUMCLOUDLAYERS`, `TECHNIQUE_COUNT`, `fBlendConstantValue`.

`BSSkyShaderProperty::GetRenderPasses` (OG `0x287C400`) selects the technique:

```
SO_CLOUDS: fBlendValue <= 0            -> 5 Clouds
           textures[0]/[1] == default  -> 7 CloudsFade  (+ bFadeSecondTexture)
           otherwise                   -> 6 CloudsLerp
SO_STARS -> 3 Stars;  SO_MOON_SHADOW -> 2;  SO_ATMOSPHERE/SKYQUAD -> 1 BasicSky
SO_SUN_GLARE -> 8;  others -> 4 Texture
```

`Clouds::Update(Sky*, float)` (OG `0x645E20`, vtable slot 2) runs when `Sky::mode` is 2 or 3:

* `Clouds::pColors[layer]` and `fAlpha[layer]` → `BSSkyShaderProperty::kBlendColor`;
* per-layer scroll bytes from `cloudLayerSpeedY/X` of `currentWeather` and `lastWeather`, blended by
  `Sky::currentWeatherPct`, scaled by frame delta and **accumulated** into
  `BSSkyShader::pCloudTexCoordOffset[layer]` (no time-of-day input);
* `fBlendValue = max(currentWeatherPct, const)`; textures reload lazily via
  `Clouds::SetBaseTexturesFromWeather` (OG `0x646710`) on weather change.

## 4. Sky shader interface

```
BSSkyShaderTechniques  SunOcclude 0 | BasicSky 1 | MoonAndStarsMask 2 | Stars 3 |
                       Texture 4 | Clouds 5 | CloudsLerp 6 | CloudsFade 7 | SunGlare 8

Vertex constants  WorldViewProj 0 | World 1 | BlendColor 2 | EyePosition 3 |
                  TexCoordOff 4 | PreviousWorld 5
Pixel constants   PParams 0
Samplers          BaseSampler 0 | BlendSampler 1 | NoiseGradSampler 2
```

`BSSkyShader::SetupGeometry` (OG `0x287B130`, vtable slot 7):

* `TexCoordOff` ← `pCloudTexCoordOffset[property->usCloudLayer]`;
* `BlendColor` ← `property->kBlendColor` (CloudsFade with `bFadeSecondTexture == false` substitutes
  `K - fBlendValue`);
* texture slot 0 ← `textures[0]`, slot 1 ← `textures[1]` (CloudsLerp), CloudsFade picks one;
* sampler slot 2 (`NoiseGradSampler`) is bound to a global noise-gradient texture for every technique;
* per-technique 12-float color constant ← `kBlendColor`^power + two global palettes (atmosphere uses
  `pSkyColor[3]`^power).

`BSSkyShader::SetupTechnique` (OG `0x287ADD0`, vtable slot 2) maps technique → VS/PS id through
`BSSkyShaderMacros` and sets `BSGraphics::RendererShadowState` blend/depth modes. Techniques 4–7
share one state group (`alphaBlendMode = 1`, `rasterStateDepthBiasMode = 4`, update flag `0x10`);
BasicSky is opaque-ish; Stars/MoonAndStarsMask and SunGlare differ. The numeric D3D11 enum meanings
are not decoded.

## 5. Per-frame driver data

`Sky::Update(float)` (OG `0x64DA60`, high confidence, not symbol-matched) runs
`Sky::UpdateWeather` (OG `0x64E530`), `Sky::UpdateFog` (OG `0x64F950`), `Sky::UpdateEffects`
(OG `0x655280`), `Sky::HandleClimateChange` (OG `0x651570`), the `SkyObject::Update` virtuals for
`Atmosphere (+0x70)`, `Stars (+0x78)`, `Clouds (+0x88)`, `Sun (+0x80)`, both moons (+0x90/+0x98), and
`Precipitation::Update` (OG `0x649480`) on `+0xA0`.

`Sky::UpdateWeather` computes the weather blend from wall time:

```
currentWeatherPct (+0x360) =
    ((currentGameHour (+0x358) + dt) - lastWeatherUpdate (+0x35C))
  / (currentWeather->weatherData[3] (TESWeather+0xA6F) * scale * (max-min) + min)
```

clamped to 0..1 and smoothed with `accelBeginPct (+0x390)`.

## 6. Hook recommendation and D3D access

* D3D is reachable without a `Present` hook: `BSGraphics::GetRendererData()` (Address Library
  id 1235449, OG global pointer `0x609BF80`) gives `pDevice (+0x48)`, `pContext (+0x50)`,
  `RenderWindowA[32] (+0x58)`, `pRenderTargetsA[101] (+0xA58)`,
  `pDepthStencilTargetsA[13] (+0x1D48)` (`BSGraphics::RendererData`, `sizeof 0x25C0`).
* `BSGraphics::DepthStencilTarget` (`sizeof 0x98`): `pTexture +0`, `pDSView[4] +0x08`,
  `pDSViewReadOnlyDepth[4] +0x28`, `pSRViewDepth +0x88`.
* Main color/depth logical ids: `RenderTargetID::kMain = 1`, `DepthStencilTargetID::kMain = 1`.
* Recommended insertion: call original `BSShaderAccumulator::RenderGeometryGroup` (OG `0x282F110`),
  then if `group == 0xE` (`GG_SKYCLOUDS`) run a custom pass — once per
  `BSGraphics::State::frameID (+0x9C)` because `FUN_14282e300` also calls `RenderGeometryGroup`.

## 7. Address table (OG 1.10.163)

Image base `0x140000000`. `NM` = symbol-name match in the 1.10.163 corpus; `VT` = RTTI→vtable→slot;
`DC` = stored Ghidra decompile; `AL` = Address Library id → RVA.

| Symbol | OG RVA | AE 1.11.240 RVA | Evidence |
|---|---|---|---|
| `Sky::Singleton` | `0x128CB0` | `0x2F2730` | AL id 484694 |
| `Sky` vtable | `0x2CBFCD8` | — | AL id 12448 |
| `Sky::Update` | `0x64DA60` | — | DC + NM (high) |
| `Sky::UpdateWeather` | `0x64E530` | — | NM + DC |
| `Sky::UpdateFog` | `0x64F950` | — | NM |
| `Sky::UpdateEffects` | `0x655280` | — | NM |
| `Sky::HandleClimateChange` | `0x651570` | — | NM |
| `Sky::FillCloudColorBlendColors` | `0x653620` | — | NM + DC |
| `Clouds` vtable | `0x2CBF5F8` | — | AL id 800360 |
| `Clouds::Update` | `0x645E20` | — | VT + NM + DC |
| `Clouds::SetBaseTexturesFromWeather` | `0x646710` | — | NM |
| `Clouds::RemoveTextures` | `0x646520` | — | NM |
| `Atmosphere` vtable | `0x2CBF5B8` | — | AL id 627676 |
| `Atmosphere::Update` | `0x644BD0` | — | NM + DC |
| `BSSkyShader` vtable | `0x30990C8` | — | AL id 221629 |
| `BSSkyShader::SetupTechnique` (slot 2) | `0x287ADD0` | `0x221ACB0` | VT + DC |
| `BSSkyShader::SetupGeometry` (slot 7) | `0x287B130` | `0x221B020` | VT + DC |
| `BSSkyShader::RestoreGeometry` (slot 8) | `0x287BAD0` | — | VT |
| `BSSkyShaderProperty` vtable | `0x30991E8` | — | AL id 207940 |
| `BSSkyShaderProperty::GetRenderPasses` | `0x287C400` | — | NM + DC |
| `BSBatchRenderer::RenderBatches` | `0x287F380` | — | NM + DC |
| `BSBatchRenderer::RenderBatchesInOrder` | `0x287F4E0` | — | NM + DC |
| `BSBatchRenderer::GeometryGroup::Render` | `0x28808F0` | — | NM + DC |
| `BSBatchRenderer::RegisterPass` | `0x28818E0` | — | NM |
| `BSShaderAccumulator::RenderAllBatches` | `0x282EEF0` | — | NM + DC |
| `BSShaderAccumulator::RenderGeometryGroup` | `0x282F110` | — | NM + DC |
| `BSShaderAccumulator::FinishAccumulating_Standard_PreResolveDepth` | `0x282DD00` | — | NM + DC |
| `BSShaderAccumulator::FinishAccumulatingPostResolveDepth` | `0x282DCB0` | — | NM + DC |
| `PersistentPassList::AlphaSort` | `0x287D8F0` | — | NM |
| `BSGraphics::GetRendererData` | global `0x609BF80` | — | AL id 1235449 |

## 8. Open questions

1. Runtime depth format, MSAA sample count, `sampleable` flag and whether sky geometry writes depth
   (pre-resolve phase, so depth may not be a usable SRV).
2. `Sky::Update` identity (`0x64DA60`) — verify by signature before hooking.
3. Sun direction convention: which node/light axis is the sun vector and whether `spLight` or
   `spCloudLight` should light clouds.
4. Which render target is bound at shader slot 7 and whether tonemapping has already been applied.
5. AE 1.11.240 parity of the render-sequence functions.
6. Behaviour under ENB's `d3d11.dll` proxy (device may be wrapped).
