# UE5 Cinematic Photoreal BRDF Patch

This repository contains a custom, highly-optimized Bidirectional Reflectance Distribution Function (BRDF) patch for Unreal Engine 5's Substrate material framework. 

It was originally developed for the martial arts game **VOVINAM** to achieve AAA-quality, photorealistic cinematic lighting on characters without the heavy performance cost of Lumen or native Subsurface Scattering.

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

## Installation

1. Clone the Unreal Engine 5 source code from Epic Games' official GitHub.
2. Download the `UE5_Cinematic_BRDF_Substrate.diff` patch file from this repository.
3. Place the `.diff` file in your Unreal Engine root directory and apply it using Git:
   ```bash
   git apply UE5_Cinematic_BRDF_Substrate.diff
   ```
4. Run `Setup.bat` (or `.sh` on Linux/Mac).
5. Run `GenerateProjectFiles.bat`.
6. Open the `UE5.sln` in Visual Studio and build the **UnrealEditor** target.

## License
Distributed under the **MIT License**. See `LICENSE` for more information. You are free to use this in your commercial indie games!
