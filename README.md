Tracer
======

Tracer is a C++ rendering engine that aimed to produce photorealistic images using Path Tracing techniques on CPU.

Screenshots
------

* USD Kitchen, using the UDPT, Diffuse, Position, Normal and Debug integrators:

<img src="https://i.ibb.co/hch2YHf/tracer-render-udpt.png" width="320" height="180"> <img src="https://i.ibb.co/KDcwzGG/tracer-render-diffuse.png" width="320" height="180">
<img src="https://i.ibb.co/209PjBG/tracer-render-position.png" width="320" height="180"> <img src="https://i.ibb.co/87sh556/tracer-render-normal.png" width="320" height="180">
<img src="https://i.ibb.co/tCm78Z5/tracer-render-debug.png" width="320" height="180">

Features
------

* Rendering:
    * Progressive rendering
    * Render/export to PPM
    * Render/export to EXR

* Camera:
    * Types:
        * FPS
        * **TODO: ** DCC-style
    * Subpixel jitter antialiasing
    * Depth of Field (using aperture radius and focal distance)

* Integrator:
    * UDPT (Unidirectional Path Tracing) (**WIP**)
    * Diffuse (**WIP**)
    * **TODO :** Occlusion
    * Position
    * Normal
    * Debug
        * Render the equivalent of Pixar USD's primID on the geometry

* Sampling:
    * RNG:
        * Uniform (jittered)
        * Stratified (**WIP**)
    * Methods:
        * Hemisphere:
            * Uniform
            * Cosine weighted
        * Sphere:
            * Uniform

* Material:
    * **TODO :** Default
    * **TODO :** Diffuse
    * **TODO :** Empirical (For experiment purposes)
    * **TODO :** Disney (2012)

* BSDF/Lobes:
    * Diffuse:
        * **TODO :** Lambert
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
    * Sky light
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

Tracer was written using Linux, VSCode as the IDE, CMake as the building tool, and a C++14 compiler in mind.

Download the source, build the project structure using CMake 3.x, open the project using your favorite IDE (tested on QtCreator), build the project, and everything should be ready to use.

* In Tracer :
    * Hold the right mouse button to use the camera
    * Use the "+" and "-" buttons on the keypad control the aperture radius
    * Hold LeftCtrl and "+" or "-" to control the focal distance

Dependencies (included, aside from Intel Embree/TBB, as well as Pixar USD and its own dependencies)
------

- Window&Input System: GLFW
- OpenGL Functions Loader: GLAD
- GUI System: dear imgui
- EXR Handling: tinyexr
- Image Loading: stb
- Scene Loading: Pixar USD
- Ray Tracing Kernels: Intel Embree
- Multithreading: Intel TBB
