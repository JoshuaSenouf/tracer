find_package(embree 3.0 REQUIRED)

if(NOT embree_FOUND)
    message(FATAL_ERROR "Could not find Embree!")
else()
    message(STATUS "Found Embree (${EMBREE_VERSION})!")
    message(STATUS "    EMBREE_INCLUDE_DIRS: ${EMBREE_INCLUDE_DIRS}")
    message(STATUS "    EMBREE_LIBRARIES: ${EMBREE_LIBRARIES}")
endif()
