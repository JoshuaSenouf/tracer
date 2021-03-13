file(GLOB TRACER_SOURCES
    bsdf/*.cpp
    camera/*.cpp
    context/*.cpp
    # gui/imgui/*.cpp
    # gui/qt/*.cpp
    integrator/*.cpp
    material/*.cpp
    math/*.cpp
    object/*.cpp
    opengl/*.cpp
    renderer/*.cpp
    sampling/*.cpp
    scene/*.cpp
    utility/*.cpp
    *.cpp
)

add_executable(
    ${PROJECT_NAME}
    main.cpp
    ${TRACER_SOURCES}
)

target_link_libraries(
    ${PROJECT_NAME}
    cli11
    embree_common
    glad
    imgui
    spdlog
    tinyexr
    ${Boost_LIBRARIES}
    ${EMBREE_LIBRARIES}
    ${GLFW_LIBRARIES}
    ${TBB_LIBRARIES}
    ${USD_LIBRARIES}
)

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
