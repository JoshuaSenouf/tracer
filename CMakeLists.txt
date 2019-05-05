cmake_minimum_required(VERSION 3.0)
project(tracer)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/api/cmake)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(api/glfw)

find_package(USD REQUIRED)
find_package(PythonLibs 2.7 REQUIRED)
find_package(
    Boost REQUIRED
    COMPONENTS regex system filesystem thread date_time atomic python)
find_package(embree 3.0 REQUIRED)

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
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /O2 /openmp")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -Wpedantic -std=c++11 -fopenmp")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories(api/glad/include/
                    api/glfw/include/
                    api/stb/
                    api/imgui/
                    api/tinyobjloader/
                    api/tinyexr/
                    src/camera/
                    src/gui/
                    src/math/
                    src/objects/
                    src/objects/geometry/
                    src/objects/lights/
                    src/rendering/
                    src/rendering/integrators/
                    src/rendering/materials/
                    src/scene/
                    src/utility/
                    ${USD_INCLUDE_DIR}
                    ${PYTHON_INCLUDE_PATH}
                    ${EMBREE_INCLUDE_DIRS})

file(GLOB API_SOURCES api/glad/src/glad.c
                      api/imgui/*.cpp)

file(GLOB PROJECT_HEADERS src/camera/*.h
                          src/gui/*.h
                          src/math/*.h
                          src/objects/*.h
                          src/objects/geometry/*.h
                          src/objects/lights/*.h
                          src/rendering/*.h
                          src/rendering/integrators/*.h
                          src/rendering/materials/*.h
                          src/scene/*.h
                          src/utility/*.h
                          src/*.h)

file(GLOB PROJECT_SOURCES src/camera/*.cpp
                          src/gui/*.cpp
                          src/math/*.cpp
                          src/objects/*.cpp
                          src/objects/geometry/*.cpp
                          src/objects/lights/*.cpp
                          src/rendering/*.cpp
                          src/rendering/integrators/*.cpp
                          src/rendering/materials/*.cpp
                          src/scene/*.cpp
                          src/utility/*.cpp
                          src/*.cpp)

file(GLOB PROJECT_SHADERS res/shaders/*.frag
                          res/shaders/*.glsl
                          res/shaders/*.vert)

file(GLOB PROJECT_SCENES res/scenes/*.usd
                         res/scenes/*.usda
                         res/scenes/*.usdc)

file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          README.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

source_group("API" FILES ${API_SOURCES})
source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Scenes" FILES ${PROJECT_SCENES})


add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

add_executable(${PROJECT_NAME} ${API_SOURCES}
                               ${PROJECT_SOURCES}
                               ${PROJECT_HEADERS}
                               ${PROJECT_SHADERS}
                               ${PROJECT_SCENES}
                               ${PROJECT_CONFIGS})

target_link_libraries(${PROJECT_NAME}
                      glfw
                      ${GLFW_LIBRARIES}
                      ${GLAD_LIBRARIES}
                      ${USD_LIBS}
                      ${EMBREE_LIBRARY})

set_target_properties(${PROJECT_NAME} PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
