cmake_minimum_required(VERSION 3.1.0)
project(tracer)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/thirdparty/cmake)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS
    Core
    Gui
    Quick
    QuickWidgets
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
    Qt5::Quick
    Qt5::QuickWidgets
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
    src/bsdf
    src/camera
    src/context
    # src/gui
    src/integrator
    src/material
    src/math
    src/object
    # src/opengl
    src/renderer
    src/sampling
    src/scene
    src/utility
    src/viewport
    ${USD_INCLUDE_DIR}
    ${PYTHON_INCLUDE_PATH}
    ${EMBREE_INCLUDE_DIRS}
    ${TBB_INCLUDE_DIRS})

file(GLOB THIRDPARTY_SOURCES
    )

file(GLOB PROJECT_HEADERS
    src/bsdf/*.h
    src/camera/*.h
    src/context/*.h
    # src/gui/*.h
    src/integrator/*.h
    src/material/*.h
    src/math/*.h
    src/object/*.h
    # src/opengl/*.h
    src/renderer/*.h
    src/sampling/*.h
    src/scene/*.h
    src/utility/*.h
    src/viewport/*.h
    src/*.h)

file(GLOB PROJECT_SOURCES
    src/bsdf/*.cpp
    src/camera/*.cpp
    src/context/*.cpp
    # src/gui/*.cpp
    src/integrator/*.cpp
    src/material/*.cpp
    src/math/*.cpp
    src/object/*.cpp
    # src/opengl/*.cpp
    src/renderer/*.cpp
    src/sampling/*.cpp
    src/scene/*.cpp
    src/utility/*.cpp
    src/viewport/*.cpp
    src/*.cpp)

file(GLOB PROJECT_QT
    res/qml/*.qrc
    res/qml/*.qml
    res/qml/qmldir
    res/qml/logger/*.qrc
    res/qml/logger/*.qml
    res/qml/logger/qmldir
    res/qml/renderconfig/*.qrc
    res/qml/renderconfig/*.qml
    res/qml/renderconfig/qmldir
    res/qml/scenegraph/*.qrc
    res/qml/scenegraph/*.qml
    res/qml/scenegraph/qmldir
    res/qml/viewport/*.qrc
    res/qml/viewport/*.qml
    res/qml/viewport/qmldir)

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
source_group("Qt" FILES ${PROJECT_QT})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Scenes" FILES ${PROJECT_SCENES})

add_definitions(-DGLFW_INCLUDE_NONE
    -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

add_executable(${PROJECT_NAME} ${THIRDPARTY_SOURCES}
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
    ${PROJECT_QT}
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
