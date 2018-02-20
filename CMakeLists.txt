cmake_minimum_required(VERSION 3.0)
project(Tracer)

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

include_directories(src/camera/
                    src/geometry/
                    src/gui/
                    src/math/
                    src/rendering/
                    src/scene/
                    src/utility/
                    api/glad/include/
                    api/glfw/include/
                    api/stb/
                    api/imgui/
                    api/tinyobjloader/
                    api/tinyxml2/
                    api/tinyexr/
                    ${USD_INCLUDE_DIR}
                    ${PYTHON_INCLUDE_PATH})

file(GLOB API_SOURCES api/glad/src/glad.c
                      api/imgui/*.cpp
                      api/tinyxml2/*.cpp)

file(GLOB PROJECT_HEADERS src/camera/*.h
                          src/geometry/*.h
                          src/gui/*.h
                          src/math/*.h
                          src/rendering/*.h
                          src/scene/*.h
                          src/utility/*.h)

file(GLOB PROJECT_SOURCES src/camera/*.cpp
                          src/geometry/*.cpp
                          src/gui/*.cpp
                          src/math/*.cpp
                          src/rendering/*.cpp
                          src/scene/*.cpp
                          src/utility/*.cpp
                          src/*.cpp)

file(GLOB PROJECT_SHADERS res/shaders/*.glsl
                          res/shaders/*.frag
                          res/shaders/*.vert)

file(GLOB PROJECT_SCENES res/scenes/xml/*.xml
                         res/scenes/usd/*.usd
                         res/scenes/usd/*.usda
                         res/scenes/usd/*.usdc)

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

add_executable(${PROJECT_NAME} ${API_SOURCES} ${PROJECT_SOURCES}
                               ${PROJECT_HEADERS} ${PROJECT_SHADERS}
                               ${PROJECT_SCENES} ${PROJECT_CONFIGS})

target_link_libraries(${PROJECT_NAME} glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES}
                      ${USD_LIBS})

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
