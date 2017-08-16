Tracer
======

Tracer is a C++ rendering engine that aimed to produce photorealistic images using Path Tracing techniques on CPU.

How to use
------

Tracer was written using Linux, QtCreator as the IDE, CMake as the building tool, and a C++11 compiler in mind.

Download the source, build the project structure using CMake 3.x, open the project using your favorite IDE (tested on QtCreator), build the project, and everything should be ready to use.


Dependencies (included, aside from OpenMP)
------

- Window & Input system : GLFW
- GUI system : dear imgui
- OpenGL Function Loader : GLAD
- OpenGL Mathematic Functions : GLM
- Mesh Loading : tinyobjloader
- Multithreading : OpenMP
