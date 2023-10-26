find_package(TBB 2020 REQUIRED)

if(NOT TBB_FOUND)
    message(FATAL_ERROR "Could not find TBB!")
else()
    message(STATUS "Found TBB (${TBB_VERSION})!")
    message(STATUS "    TBB_INCLUDE_DIRS: ${TBB_INCLUDE_DIRS}")
    message(STATUS "    TBB_LIBRARIES: ${TBB_LIBRARIES}")
endif()
