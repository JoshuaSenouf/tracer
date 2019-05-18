Tracer
======

Tracer is a C++ rendering engine that aimed to produce photorealistic images using Path Tracing techniques on CPU.

Screenshots
------

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

* Material:
    * Lambertian diffuse
    * Specular component:
        * Roughness/metalness workflow
        * Still an empirical WIP before a switch to Beckmann or GGX
    * **TODO :** Physically-based BSDF (Probably a simplified version of the Disney principled BSDF)

* Light sources:
    * Geometry light
    * Sky light

* Geometry types:
    * Meshes
        * Triangle-based
        * Quad-based 
        * **TODO :**  Subdivided
    * **TODO :** Curves
    * **TODO :** Primitives (sphere, cube...)
    * Instances:
        * Per-geometry single instancing
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
        * **TODO :** Settings loading

* Utility:
    * GUI using ImGui
    * Pause/resume render
    * Front/backbuffer swapping
    * FPS counter

How to use
------

Tracer was written using Linux, QtCreator as the IDE, CMake as the building tool, and a C++11 compiler in mind.

Download the source, build the project structure using CMake 3.x, open the project using your favorite IDE (tested on QtCreator), build the project, and everything should be ready to use.

* In Tracer :
    * Hold the right mouse button to use the camera
    * Use the "+" and "-" buttons on the keypad control the aperture radius
    * Hold LeftCtrl and "+" or "-" to control the focal distance

Dependencies (included, aside from Pixar USD and its own dependencies)
------

- Window & Input system: GLFW
- OpenGL Function Loader: GLAD
- GUI system: dear imgui
- Multithreading: Intel TBB
- EXR handling: tinyexr
- Mesh loading: tinyobjloader
- Image loading: stb
- Scene loading: Pixar USD
- Ray tracing kernels: Intel Embree
