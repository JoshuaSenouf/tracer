cmake_minimum_required(VERSION 3.0)
project(Tracer)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(api/glfw)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories(src/camera/
                    src/renderer/
                    src/resources/
                    api/glad/include/
                    api/glfw/include/
                    api/glm/
                    api/stb/
                    api/imgui/
                    api/embree/include
                    api/tbb/include)

file(GLOB API_SOURCES api/glad/src/glad.c
                        api/imgui/*.cpp)

file(GLOB PROJECT_HEADERS src/camera/*.h
                          src/renderer/*.h
                          src/resources/*.h)

file(GLOB PROJECT_SOURCES src/camera/*.cpp
                          src/renderer/*.cpp
                          src/resources/*.cpp
                          src/*.cpp)

file(GLOB PROJECT_SHADERS res/shaders/*.glsl
                          res/shaders/*.frag
                          res/shaders/*.vert)

file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          README.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("API" FILES ${API_SOURCES})

set(TBB_DIR "api/tbb/cmake" CACHE FILEPATH "TBB CMake directory that include every .cmake files")
find_package(TBB REQUIRED)

set(EMBREE_DIR "api/embree" CACHE FILEPATH "Embree CMake directory that include every .cmake files")
find_package(EMBREE 2.16.4 REQUIRED)

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                               ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
                               ${API_SOURCES})

target_link_libraries(${PROJECT_NAME} glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES}
                      ${TBB_IMPORTED_TARGETS}
                      ${EMBREE_IMPORTED_TARGETS})

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
