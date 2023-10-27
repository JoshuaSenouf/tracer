file(GLOB TRACER_SOURCES
    bsdf/*.cpp
    camera/*.cpp
    context/*.cpp
    gui/imgui/*.cpp
    integrator/*.cpp
    material/*.cpp
    math/*.cpp
    object/*.cpp
    opengl/*.cpp
    renderer/*.cpp
    sampling/*.cpp
    scene/*.cpp
    utility/*.cpp
)

add_executable(
    ${PROJECT_NAME}
    main.cpp
    ${TRACER_SOURCES}
)

target_link_libraries(
    ${PROJECT_NAME}
    # Internal dependencies.
    cli11
    embree_common
    glad
    imgui
    pcg
    spdlog
    tinyexr
    # External dependencies.
    ${EMBREE_LIBRARIES}
    ${GLFW_LIBRARIES}
    ${TBB_LIBRARIES}
    ${PXR_LIBRARIES}
)

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
