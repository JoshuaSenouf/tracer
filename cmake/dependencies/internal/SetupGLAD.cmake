file(GLOB THIRDPARTY_GLAD_SOURCES
    "glad/src/*.c"
)

add_library(
    glad
    ${THIRDPARTY_GLAD_SOURCES}
)

target_include_directories(
    glad PUBLIC
    "glad/include"
)
