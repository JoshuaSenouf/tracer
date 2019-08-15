# Simplified version of Victor Yudin's script

# Trying to find USD include path.
find_path (
    USD_INCLUDE_DIR
    pxr/pxr.h
    PATHS $ENV{USD_ROOT}/include
    NO_DEFAULT_PATH)

# The list of required libraries for minimal USD.
set (_usd_components
    usdImagingGL
    usdImaging
    usdHydra
    hdx
    hdSt
    hd
    glf
    garch
    pxOsd
    usdRi
    usdUI
    usdShade
    usdGeom
    usd
    usdUtils
    trace
    pcp
    sdf
    plug
    js
    ar
    work
    tf
    kind
    arch
    vt
    gf
    hf
    cameraUtil
    usdLux)

set (USD_LIBRARIES "")

# Trying to find all the libraries.
foreach (COMPONENT ${_usd_components})
    string (TOUPPER ${COMPONENT} UPPERCOMPONENT)

    unset (USD_${UPPERCOMPONENT}_LIBRARY CACHE)

    find_library (
        USD_${UPPERCOMPONENT}_LIBRARY
        NAMES ${COMPONENT} ${COMPONENT}${CMAKE_STATIC_LIBRARY_SUFFIX} lib${COMPONENT}${CMAKE_STATIC_LIBRARY_SUFFIX}
        PATHS $ENV{USD_ROOT}/lib
        NO_DEFAULT_PATH)

    list(APPEND USD_LIBRARIES ${USD_${UPPERCOMPONENT}_LIBRARY})
endforeach ()
