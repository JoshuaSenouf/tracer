cmake_minimum_required(VERSION 3.12)

project(tracer
    VERSION 1.0
    DESCRIPTION "Renderer using C++, Embree and USD to achieve Path Tracing techniques on the CPU."
    HOMEPAGE_URL "https://github.com/JoshuaSenouf/tracer"
    LANGUAGES C CXX
)

# Adding CMake modules
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_SOURCE_DIR}/cmake/dependencies/external
    ${CMAKE_SOURCE_DIR}/cmake/dependencies/internal
    ${CMAKE_SOURCE_DIR}/cmake/modules
    ${CMAKE_SOURCE_DIR}/cmake/setup
)

# Project CMake setup
include(Options)
include(CXX)

# Setup external dependencies
# include(SetupBoost)
include(SetupTBB)
include(SetupEmbree)
include(SetupGLFW)
include(SetupUSD)

add_subdirectory(thirdparty)
add_subdirectory(cpp)
