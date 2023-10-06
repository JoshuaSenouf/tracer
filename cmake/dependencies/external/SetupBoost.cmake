set(Boost_NO_BOOST_CMAKE ON)
set(Boost_NO_SYSTEM_PATHS ON)
set(Boost_ROOT $ENV{REZ_BOOST_ROOT})
set(BOOST_INCLUDEDIR ${Boost_ROOT}/include)
set(BOOST_LIBRARYDIR ${Boost_ROOT}/lib)

find_package(Boost 1.80 REQUIRED COMPONENTS
    regex
    system
    filesystem
    thread
    date_time
    atomic
)

include_directories(
    ${Boost_INCLUDE_DIRS}
)

set(Boost_LIBRARIES "${Boost_LIBRARIES}" CACHE INTERNAL "Boost_LIBRARIES")
set(Boost_INCLUDE_DIRS "${Boost_INCLUDE_DIRS}" CACHE INTERNAL "Boost_INCLUDE_DIRS")
