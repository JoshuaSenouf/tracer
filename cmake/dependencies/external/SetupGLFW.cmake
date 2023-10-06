find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(glfw3 REQUIRED)

include_directories(${GLFW_INCLUDE_DIRS})

set(GLFW_INCLUDE_DIRS "${GLFW_INCLUDE_DIRS}" CACHE INTERNAL "GLFW_INCLUDE_DIRS")
set(GLFW_LIBRARIES "${GLFW_LIBRARIES}" CACHE INTERNAL "GLFW_LIBRARIES")