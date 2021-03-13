add_library(
    embree_common INTERFACE
)

target_include_directories(
    embree_common INTERFACE
    "embree/include"
)
