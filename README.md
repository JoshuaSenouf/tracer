Tracer
======

Tracer is a C++ rendering engine that aimed to produce photorealistic images using Path Tracing techniques on CPU.

Screenshots
------

* Cornell Box (800x600, 4 bounces, 1spp, after ~5 minutes on an i5-5200U) :

![](https://image.ibb.co/gEqMBR/tracer_Render_cornell.png)


* Low light (800x600, 4 bounces, 1spp, after ~5 minutes on an i5-5200U) :

![](https://image.ibb.co/hzNq5m/tracer_Render_low_Light.png)


Features
------

* Rendering :
    * Progressive rendering
    * Render/export to PPM
    * Render/export to EXR

* Camera :
    * Movements
        * Subpixel jitter antialiasing
        * Depth of Field (using aperture radius and focal distance)

* Material :
    * **TODO :** Physically-based BSDF (Probably a simplified version of the Disney principled BSDF)

* Light sources :
    * Emissive spheres
    * Sky light

* Shapes :
    * Spheres
    * **TODO :** Planes/boxes
    * **TODO :** Triangles

* Acceleration structure :
    * **TODO :** BVH
    * **TODO :** KD-Tree

* Scene :
    * XML scene format, with associated parser
    * Materials loading
    * Spheres loading
    * **TODO :** Meshes loading
    * **TODO :** Camera loading
    * **TODO :** Configuration loading

* Utility :
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

Dependencies (included, aside from OpenMP)
------

- Window & Input system : GLFW
- OpenGL Function Loader : GLAD
- GUI system : dear imgui
- Multithreading : OpenMP
- XML handling : TinyXML2
- EXR handling : tinyexr
- Mesh Loading : tinyobjloader
- Image loading : stb
