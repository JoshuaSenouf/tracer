Tracer
======

Tracer is a C++ rendering engine that aimed to produce photorealistic images using Path Tracing techniques on CPU.

Screenshots
------

* Glossy sphere and DoF (1280x720, 4 bounces, 1spp, after ~1.5 minutes on an i7-6700K) :

![](https://image.ibb.co/bW14U6/mono_Sphere_Do_F_720p.png)

* Low light material test (1280x720, 4 bounces, 1spp, after ~2 minutes on an i7-6700K) :

![](https://image.ibb.co/cxF9wm/material_Test_720p.png)

* Cornell Box (1280x720, 4 bounces, 1spp, after ~3 minutes on an i7-6700K) :

![](https://image.ibb.co/nD0bbm/cornell_720p.png)

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
    * Lambertian diffuse.
    * Specular component:
        * Roughness/metalness workflow.
        * Still an empirical WIP before a switch to Beckmann or GGX.
    * **TODO :** Physically-based BSDF (Probably a simplified version of the Disney principled BSDF)

* Light sources:
    * Geometry light
    * Sky light

* Primitives:
    * Sphere
    * **TODO :** Quad
    * **TODO :** Cube
    * **TODO :** Triangle

* Acceleration structure:
    * **TODO :** BVH
    * **TODO :** KD-Tree

* Scene:
    * **TODO :** Custom JSON format
    * **TODO :** Scene Graph
    * Material loading
    * Primitives loading:
        * Sphere
        * **TODO :** Quad
        * **TODO :** Cube
        * **TODO :** Triangle
    * **TODO :** Mesh loading
    * Light loading
    * Camera loading
    * Settings loading

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

Dependencies (included, aside from Intel Embree and Intel TBB)
------

- Window & Input system : GLFW
- OpenGL Function Loader : GLAD
- GUI system : dear imgui
- EXR handling : tinyexr
- Mesh loading : tinyobjloader
- Image loading : stb

-  **TODO :** JSON handling : ???
-  **TODO :** Multithreading : Intel TBB
-  **TODO :** Raytracing kernels: Intel Embree