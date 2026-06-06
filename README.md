# UE5 Cinematic Photoreal BRDF Patch

This repository contains a custom, highly-optimized Bidirectional Reflectance Distribution Function (BRDF) patch for Unreal Engine 5's Substrate material framework. 

**Inspiration:** The mathematical models injected here are heavily inspired by the phenomenal rendering techniques presented by Striking Distance Studios (*The Callisto Protocol*) at SIGGRAPH 2023.

## Features

This patch modifies `SubstrateEvaluation.ush` to replace the default engine lighting math with three advanced phenomenological models:

1. **Disney-Style Diffuse (Fresnel & Retroreflection):**
   Replaces the standard Lambert diffuse. It accurately scatters light at grazing angles and bounces light back towards the camera on rough surfaces (like fabric and skin pores), giving characters a fleshy, "living" look.
2. **Smooth Terminator:**
   Replaces the harsh `max(0, dot(N, L))` shadow cutoff with a custom smoothstep function. This eliminates jagged, pitch-black shadow edges on lower-poly character geometry.
3. **Dual GGX Specular:**
   Replaces the single GGX reflection lobe with a layered Dual GGX approach. It evaluates two separate specular lobes (one sharp, one broad) and blends them to mathematically simulate the complex layering of skin oils and wet sweat.

## Performance
**Extremely Optimized.** Because these are mathematical shader modifications (adding ~15 basic arithmetic instructions per pixel), the performance impact is virtually zero (fractions of a millisecond). It is massively faster than trying to achieve the same visual fidelity using Lumen or standard Subsurface Profile materials.

## Under the Hood: The Mathematics

For graphics programmers interested in how this alters the standard Unreal Engine evaluation loop:

### 1. Disney Diffuse
Unreal's default `Diffuse_Lambert` simply returns `DiffuseColor / PI`. We replace this with a full Disney diffuse formulation. We calculate Fresnel for both the Light vector (`NoL`) and the View vector (`NoV`) using a 5th-power approximation (`pow(1.0f - NoL, 5)`). We then mix this with a retroreflective peak that scales directly with the material's roughness. This pushes light into the grazing angles of the geometry, faking complex subsurface light transport.

### 2. Smooth Terminator
The classic "terminator problem" causes jagged shadows on low-tessellation models where `dot(N, L)` abruptly hits zero. We mitigate this by shifting and smoothing the boundary. We take the `NoL`, multiply it by 2 to stretch the gradient, and push it through a cubic smoothstep function `(3x^2 - 2x^3)`. This forces the lighting to gracefully fade out just before the shadow boundary, hiding geometry faceting.

### 3. Dual GGX
Standard UE5 Substrate slabs evaluate a single GGX microfacet distribution. To fake sweaty skin, we calculate the primary `D` (Distribution) and `Vis` (Visibility/Shadowing) terms using the material's base roughness. Then, we artificially generate a *secondary* roughness value (`saturate(SafeRoughness * 2.0f + 0.1f)`) to create a broader, softer underlying specular lobe. We then `lerp` these two lobes together. The sharp lobe handles the pinpoint wet glints, while the broad lobe handles the oily sheen.

## Installation

1. Clone the Unreal Engine 5 source code from Epic Games' official GitHub.
2. Download the `UEDualGGX.diff` patch file from this repository.
3. Place the `.diff` file in your Unreal Engine root directory and apply it using Git:
   ```bash
   git apply UEDualGGX.diff
   ```
4. Run `Setup.bat` (or `.sh` on Linux/Mac).
5. Run `GenerateProjectFiles.bat`.
6. Open the `UE5.sln` in Visual Studio and build the **UnrealEditor** target.

## License
Distributed under the **MIT License**. See `LICENSE` for more information. You are free to use this in your commercial indie games!
