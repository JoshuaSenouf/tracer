find_package(pxr REQUIRED)

if(NOT pxr_FOUND)
    message(FATAL_ERROR "Could not find USD!")
else()
    message(STATUS "Found USD (${PXR_MINOR_VERSION}.${PXR_PATCH_VERSION})!")
    message(STATUS "    PXR_INCLUDE_DIRS: ${PXR_INCLUDE_DIRS}")
    message(STATUS "    PXR_LIBRARIES: ${PXR_LIBRARIES}")
endif()
