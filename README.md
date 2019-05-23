Tracer
======

Tracer is a C++ rendering engine that aimed to produce photorealistic images using Path Tracing techniques on CPU.

Screenshots
------

* USD Kitchen, using the Debug integrator, displaying the equivalent of Pixar USD's primID on the geometry:

 <img src="https://i.ibb.co/XsHRpqn/primId1.png" width="640" height="320">

* Bressant 3D Scan, using the Diffuse, Position and Normal integrators:

 <img src="https://i.ibb.co/grk3sQP/bressant-diffuse.png" width="180" height="320"><img src="https://i.ibb.co/nCFBCdX/bressant-position.png" width="180" height="320"><img src="https://i.ibb.co/GJdScYs/bressant-normals.png" width="180" height="320">

Features
------

* Rendering:
    * Progressive rendering
    * Render/export to PPM
    * Render/export to EXR

* Camera:
    * Movements
    * Subpixel jitter antialiasing
    * Depth of Field (using aperture radius and focal distance)

* Integrator:
    * **TODO :** UDPT (Unidirectional Path Tracing)
    * Diffuse (WIP)
    * **TODO :** Occlusion
    * Position
    * Normal
    * Debug
        * Render the equivalent of Pixar USD's primID on the geometry

* Material:
    * **TODO :** Lambertian diffuse
    * **TODO :** Physically-based BSDF (Probably a simplified version of the Disney principled BSDF)

* Light sources:
    * **TODO :** Geometry light
    * Sky light

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
    * Ingested data:
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
