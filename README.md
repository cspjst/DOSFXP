# DOSFXP - Fast Fixed-Point Number Representation
Fast 16-bit signed 10:6 fixed-point math library in C and 8086 assembler, built for 8086+ DOS game development. Targets CGA/HGA/VGA retro resolutions.

**TLDR.** DOSFXP defines a single 16-bit signed fixed-point type, `fxp16_t`, using a 10:6 split (10 integer bits, 6 fractional bits, two's complement), stored as `int16_t`. The format yields a representable range of -512.0 to +511.984375, with a fractional resolution of 1/64 (0.015625). This range was derived empirically from candidate DOS display resolutions rather than chosen arbitrarily.

**Precision adequacy.** The chosen fractional resolution was validated against the accuracy demands of a stored trigonometric constant (π ≈ 201/64 = 3.140625, relative error ≈0.031%). Propagated through circumference-point calculation, the resulting positional error was shown to be under one pixel even at radii well beyond any listed display's dimensions, and an order of magnitude smaller than both the format's own fractional granularity and the terminal pixel-rounding step — establishing that the fixed-point format is not the limiting source of visual error in the pipeline.

**Performance and bit budget.** The IBM XT is treated as the library's computational lower bound - this dictated total format width ahead of any other consideration. The IBM XT's 16bit 8088 processor runs at only 4.77MHz and has a limited instruction set. This constrains the whole and fractional parts of a fixed point number representation to occupy exactly one 16-bit register — necessarily sacrificing precision for performance. With total width fixed at 16 bits, the integer/fractional partition becomes a zero-sum allocation (any bit gained by one part is a bit lost by the other, with no option to independently widen both) but how to best share out the precious bits between whole and fractional parts?

**Target resolutions.** The format's whole-number magnitude requirement was evaluated against the following candidate DOS display modes:

| Mode | Resolution | Max dimension | Unsigned bits required |
| ---- | ---------- | ------------- | ---------------------- |
| CGA4 | 320 × 200  | 320           | 9                      |
| CGA6 | 640 × 200  | 640           | 10                     |
| HGA  | 720 × 348  | 720           | 10                     |
| VGA  | 640 × 480  | 640           | 10                     |
| SVGA | 800 × 600  | 800           | 10                     |
| XGA  | 1024 × 768 | 1024          | 11                     |

On the reasoning that SVGA and XGA hardware are atypical of genuine 8086/8088-class systems (the library's stated target), the effective design ceiling was constrained to CGA, HGA, and VGA, of which HGA's 720 px width is the largest single dimension.

**Logical Coordinate Options.** Arising from the design ceilings are 3 examples of Cartesian coordinate models that can inform the whole part bit allocation:

| Mode | X range     | Y range     |
| ---- | ----------- | ----------- |
| CGA4 | -160 … +159 | -100 … +99  |
| HGA  | -360 … +359 | -174 … +173 |
| VGA  | -320 … +319 | -240 … +239 |

Each row represents a coordinate model sized to exactly match one display mode — CGA4's plane spans only its own ±160/±100 extent, HGA's only its own ±360/±174, and so on. Adopting this per-mode approach would allocate the whole-part bit budget as tightly as possible for whichever single resolution is active, at the cost of requiring the logical coordinate space itself to be redefined — and hence any stored positions, saved state, or level data expressed in it — each time the target display mode changes. A game designed against the CGA4 plane could not have its positions reused unmodified on HGA without rescaling every value, since -160 means something different relative to each mode's own edges.

**Coordinate model.** The library rejects the per-mode approach in favour of a single, resolution-independent logical coordinate plane, sized once to the largest of the three candidate extents (HGA, ±360/±174) rather than varying per mode. Yielding a Cartesian, Y-up, origin at the plane's centre, bounded (non-wrapping) at ±512 on each axis — chosen as the full range 10 whole bits affords, rather than stopping exactly at HGA's ±360, so that game logic, physics, and stored level data are written once against a fixed coordinate space and remain valid regardless of which display mode is active at render time. The consequence is that lower-resolution modes such as CGA4 only ever address a fraction of the plane's full extent, but this is an acceptable trade against the alternative. Further, conversion to device (VRAM) coordinates becomes trivial and fast. The VRAM unsigned, origin at top-left, Y-down is performed via a fixed per-axis offset, without scaling:
```
k_x = (screenwidth / 2)
k_y = (screenheight / 2)
.
.
.
vram_x = logical_x + k_x
vram_y = k_y - logical_y 
```
Physical pixel-aspect variation across display modes (e.g. CGA's non-square pixels) is deliberately excluded from this transform and deferred to the art/asset layer, preserving an isotropic physics plane and keeping the coordinate conversion to a few instructions per axis.

------

