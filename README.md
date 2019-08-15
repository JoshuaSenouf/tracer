Tracer
======

Tracer is a renderer using C++, Embree and USD to produce photorealistic images using Path Tracing techniques on the CPU.

Screenshots
------

* USD Kitchen, using the UDPT, Diffuse, Position, Normal and Debug integrators:

<img src="https://i.ibb.co/CPKcY58/tracer-render-udpt.png" width="320" height="180"> <img src="https://i.ibb.co/0yZdGqq/tracer-render-diffuse.png" width="320" height="180">
<img src="https://i.ibb.co/fqnQrBs/tracer-render-position.png" width="320" height="180"> <img src="https://i.ibb.co/Trg5H3W/tracer-render-normal.png" width="320" height="180">
<img src="https://i.ibb.co/xHCYrnY/tracer-render-debug.png" width="320" height="180">

Features
------

* Rendering:
    * Progressive rendering
    * Render/export to PPM
    * Render/export to EXR

* Camera:
    * Types:
        * FPS
        * **TODO :** DCC-style
    * Subpixel jitter antialiasing
    * Depth of Field (using aperture radius and focal distance)

* Integrator:
    * UDPT (Unidirectional Path Tracing):
        * **TODO :** Environment Sampling
            * **TODO :** Color-based sky/background
            * **TODO :** Image-Based Lighting (IBL)
        * **TODO :** Light Sampling/Next Event Estimation (NEE)
        * BSDF Sampling
    * Diffuse (**WIP**)
    * **TODO :** Occlusion
    * Position
    * Normal
    * Debug
        * Render the equivalent of Pixar USD's primID on the geometry

* Sampling:
    * RNG:
        * Uniform
        * Stratified (**WIP**)
    * Methods:
        * Hemisphere:
            * Uniform
            * Cosine Weighted
        * Sphere:
            * Uniform

* Material:
    * **TODO :** Default
    * **TODO :** Diffuse
    * **TODO :** Empirical (for experiment purposes)
    * **TODO :** Disney (2012)

* BSDF/Lobes:
    * Diffuse:
        * Lambert
        * **TODO :** Oren-Nayar
        * **TODO :** Burley
        * **TODO :** Sheen
        * **TODO :** Subsurface Scattering
    * Specular:
        * **TODO :** GGX
        * **TODO :** Beckmann
        * **TODO :** Clearcoat
        * **TODO :** Thin Film

* Light sources:
    * Sky/background light
    * **TODO :** Geometry light

* Geometry types:
    * Meshes
        * Triangle-based
        * Quad-based 
        * **TODO :**  Subdivided
    * **TODO :** Curves
    * **TODO :** Primitives (sphere, cube...)
    * Instances:
        * Per-geometry instancing ("Everything is an instance" philosophy)
        * **TODO :** Native, multiple instancing of geometry prototypes

* Acceleration structure:
    * Intel Embree native BVH
    * **TODO :** Custom-based

* Scene:
    * Format:
        * Pixar USD
            * As .usd/usda/usdc/usdz
    * Ingested types:
        * **TODO :** Materials
        * **TODO :** Cameras
        * Geometry:
            * Meshes
            * **TODO :** Curves
            * **TODO :** Primitives
            * **TODO :** Instances
        * **TODO :** Light sources

* Utility:
    * GUI using ImGui
    * Pause/resume render
    * Front/backbuffer swapping
    * FPS counter

How to use
------

Tracer was written using Linux, VSCode as the IDE, CMake as the building tool, and a GCC C++14 compiler in mind.

Download the source, build the project structure using CMake 3.x, open the project using your favorite IDE (tested on VSCode), build the project, and everything should be ready to use.

Dependencies
------

The versions exposed here are the ones I personally used to develop and build the project in its current state. Depending on the projects, different versions, older as newer, would certainly work.

* Included:
    * Arguments Parsing: CLI11 (1.8)
    * Logging: spdlog (1.3.1)
    * Math Operations: Intel Embree SIMD Library (3.5.2)
    * EXR Handling: tinyexr (0.9.5)
* Not Included:
    * GUI System: Qt & QtQuick (5.13)
    * Scene Description: Pixar USD (19.05)
    * Ray Tracing Kernels: Intel Embree (3.5.2)
    * Multithreading: Intel TBB (2019U5)

Credits
------

