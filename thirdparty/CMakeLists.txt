#############################
### Included dependencies ###
#############################

# GLAD
file(GLOB THIRDPARTY_GLAD_SOURCES
    "glad/src/*.c"
)

add_library(
    glad
    ${THIRDPARTY_GLAD_SOURCES}
)

include_directories(
    "thirdparty/glad/include"
)
target_include_directories(
    glad PUBLIC
    "glad/include"
)

# IMGui
file(GLOB THIRDPARTY_IMGUI_SOURCES
    imgui/*.cpp
)

add_library(
    imgui
    ${THIRDPARTY_IMGUI_SOURCES}
)

include_directories(
    "thirdparty/imgui"
)
target_include_directories(
    imgui PUBLIC
    "imgui"
)
target_link_libraries(
    imgui
    glad
    ${GLFW_LIBRARIES}
)

# SPDLog
include_directories(
    "thirdparty/spdlog"
)
