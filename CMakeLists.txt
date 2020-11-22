cmake_minimum_required(VERSION 3.12)

project(tracer
    VERSION 1.0
    DESCRIPTION "Renderer using C++, Embree and USD to achieve Path Tracing techniques on the CPU."
    HOMEPAGE_URL "https://github.com/JoshuaSenouf/tracer"
    LANGUAGES C CXX
)

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_SOURCE_DIR}/cmake/defaults
    ${CMAKE_SOURCE_DIR}/cmake/modules
)

include(Defaults)
include(CXX)
include(ThirdParty)

# add_subdirectory(res)
add_subdirectory(thirdparty)
# add_subdirectory(include)
# add_subdirectory(src)

# include_directories(
#     include/bsdf
#     include/camera
#     include/context
#     # include/gui/imgui
#     # include/gui/qt
#     include/integrator
#     # include/material
#     include/math
#     include/object
#     include/opengl
#     include/renderer
#     include/sampling
#     include/scene
#     include/utility
# )

include_directories(include)

# include_directories(
#     "thirdparty/spdlog"
# )

# file(GLOB THIRDPARTY_SOURCES
#     api/glad/src/glad.c
#     api/imgui/*.cpp
# )
# file(GLOB PROJECT_HEADERS
#     include/bsdf/*.h
#     include/camera/*.h
#     include/context/*.h
#     # include/gui/imgui/*.h
#     # include/gui/qt/*.h
#     include/integrator/*.h
#     # include/material/*.h
#     include/math/*.h
#     include/object/*.h
#     include/opengl/*.h
#     include/renderer/*.h
#     include/sampling/*.h
#     include/scene/*.h
#     include/utility/*.h
#     include/*.h
# )
# file(GLOB PROJECT_SOURCES
#     src/bsdf/*.cpp
#     src/camera/*.cpp
#     src/context/*.cpp
#     # src/gui/imgui/*.cpp
#     # src/gui/qt/*.cpp
#     src/integrator/*.cpp
#     # src/material/*.cpp
#     src/math/*.cpp
#     src/object/*.cpp
#     src/opengl/*.cpp
#     src/renderer/*.cpp
#     src/sampling/*.cpp
#     src/scene/*.cpp
#     src/utility/*.cpp
#     src/*.cpp
# )
# file(GLOB PROJECT_SHADERS
#     res/shaders/*.frag
#     res/shaders/*.glsl
#     res/shaders/*.vert
# )
# file(GLOB PROJECT_SCENES
#     res/scenes/*.usd
#     res/scenes/*.usda
#     res/scenes/*.usdc
#     res/scenes/*.usdz
# )
# file(GLOB PROJECT_CONFIGS
#     CMakeLists.txt
#     README.md
#     .gitattributes
#     .gitignore
#     .gitmodules
# )

# source_group("thirdparty" FILES ${THIRDPARTY_SOURCES})
# source_group("headers" FILES ${PROJECT_HEADERS})
# source_group("sources" FILES ${PROJECT_SOURCES})
# source_group("shaders" FILES ${PROJECT_SHADERS})
# source_group("scenes" FILES ${PROJECT_SCENES})
# source_group("configs" FILES ${PROJECT_CONFIGS})

add_definitions(
    -DGLFW_INCLUDE_NONE
    -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\"
)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    # ${THIRDPARTY_SOURCES}
    # ${PROJECT_HEADERS}
    # ${PROJECT_SOURCES}
    # ${PROJECT_SHADERS}
    # ${PROJECT_SCENES}
    # ${PROJECT_CONFIGS}
)

target_link_libraries(
    ${PROJECT_NAME}
    # ${QT_LIBS}
    glad
    imgui
    # ${EMBREE_LIBRARY}
    # ${TBB_LIBRARIES}
    # ${USD_LIBS}
)

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME}
)
