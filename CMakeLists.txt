cmake_minimum_required(VERSION 3.1.0)
project(tracer)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/thirdparty/cmake)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS
    Core
    Gui
    Widgets
    REQUIRED)
find_package(USD REQUIRED)
find_package(PythonLibs 2.7 REQUIRED)
find_package(Boost REQUIRED COMPONENTS
    regex
    system
    filesystem
    thread
    date_time
    atomic
    python)
find_package(embree 3.0 REQUIRED)
find_package(TBB REQUIRED)

set(QT_LIBS
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets)
set(USD_LIBS
    ${USD_LIBRARIES}
    ${PYTHON_LIBRARIES}
    ${Boost_ATOMIC_LIBRARY}
    ${Boost_CHRONO_LIBRARY}
    ${Boost_DATE_TIME_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_PYTHON_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_REGEX_LIBRARY})

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /O2")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -Wpedantic -std=c++14")
endif()

include_directories(
    thirdparty/CLI11
    thirdparty/embree/include
    thirdparty/spdlog
    thirdparty/tinyexr
    include/bsdf
    include/camera
    include/context
    include/gui
    include/integrator
    # include/material
    include/math
    include/object
    # include/opengl
    include/renderer
    include/sampling
    include/scene
    include/utility
    ${USD_INCLUDE_DIR}
    ${PYTHON_INCLUDE_PATH}
    ${EMBREE_INCLUDE_DIRS}
    ${TBB_INCLUDE_DIRS})

file(GLOB THIRDPARTY_SOURCES
    )

file(GLOB PROJECT_HEADERS
    include/bsdf/*.h
    include/camera/*.h
    include/context/*.h
    include/gui/*.h
    include/integrator/*.h
    # include/material/*.h
    include/math/*.h
    include/object/*.h
    # include/opengl/*.h
    include/renderer/*.h
    include/sampling/*.h
    include/scene/*.h
    include/utility/*.h
    include/*.h)

file(GLOB PROJECT_SOURCES
    src/bsdf/*.cpp
    src/camera/*.cpp
    src/context/*.cpp
    src/gui/*.cpp
    src/integrator/*.cpp
    # src/material/*.cpp
    src/math/*.cpp
    src/object/*.cpp
    # src/opengl/*.cpp
    src/renderer/*.cpp
    src/sampling/*.cpp
    src/scene/*.cpp
    src/utility/*.cpp
    src/*.cpp)

file(GLOB PROJECT_SHADERS
    res/shaders/*.frag
    res/shaders/*.glsl
    res/shaders/*.vert)

file(GLOB PROJECT_SCENES
    res/scenes/*.usd
    res/scenes/*.usda
    res/scenes/*.usdc
    res/scenes/*.usdz)

file(GLOB PROJECT_CONFIGS
    CMakeLists.txt
    README.md
    .gitattributes
    .gitignore
    .gitmodules)

source_group("ThirdParty" FILES ${THIRDPARTY_SOURCES})
source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Scenes" FILES ${PROJECT_SCENES})

add_definitions(-DGLFW_INCLUDE_NONE
    -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

add_executable(${PROJECT_NAME} ${THIRDPARTY_SOURCES}
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
    ${PROJECT_SHADERS}
    ${PROJECT_SCENES}
    ${PROJECT_CONFIGS})

target_link_libraries(${PROJECT_NAME}
    ${QT_LIBS}
    ${USD_LIBS}
    ${EMBREE_LIBRARY}
    ${TBB_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
