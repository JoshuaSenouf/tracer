# Simplified version of Victor Yudin's script

# Trying to find USD include path.
find_path (
    USD_INCLUDE_DIRS
    pxr/pxr.h
    PATHS ${USD_ROOT}/include $ENV{USD_ROOT}/include
    NO_DEFAULT_PATH)

# The list of required libraries for minimal USD.
set (_usd_components
    # ar
    # arch
    # cameraUtil
    # garch
    # gf
    # glf
    # hd
    # hdSt
    # hdx
    # hf
    # js
    # kind
    # pcp
    # plug
    # pxOsd
    # sdf
    # tf
    # trace
    # usd
    # usdGeom
    # usdHydra
    # usdImaging
    # usdImagingGL
    # usdLux
    # usdRi
    # usdShade
    # usdUI
    # usdUtils
    # vt
    # work

    ar
    arch
    gf
    js
    kind
    ndr
    pcp
    plug
    sdf
    sdr
    tf
    trace
    usd
    usdGeom
    usdHydra
    usdLux
    usdMedia
    usdRender
    usdRi
    usdShade
    usdSkel
    usdUI
    usdUtils
    usdVol
    vt
    work
)

set (USD_LIBRARIES "" CACHE STRING "")

# Trying to find all the libraries.
foreach (COMPONENT ${_usd_components})
    string (TOUPPER ${COMPONENT} UPPERCOMPONENT)

    unset (USD_${UPPERCOMPONENT}_LIBRARY CACHE)

    find_library (
        USD_${UPPERCOMPONENT}_LIBRARY
        NAMES ${COMPONENT} ${COMPONENT}${CMAKE_STATIC_LIBRARY_SUFFIX} lib${COMPONENT}${CMAKE_STATIC_LIBRARY_SUFFIX}
        PATHS ${USD_ROOT}/lib $ENV{USD_ROOT}/lib
        NO_DEFAULT_PATH)

    list(APPEND USD_LIBRARIES ${USD_${UPPERCOMPONENT}_LIBRARY})
endforeach ()
