#################################
### Non-included dependencies ###
#################################

# Python
set(Python_ROOT_DIR $ENV{REZ_PYTHON_ROOT})

find_package(Python 2.7 REQUIRED Interpreter Development)

include_directories(
    ${Python_INCLUDE_DIRS}
)

# Boost
set(Boost_NO_BOOST_CMAKE ON)
set(Boost_NO_SYSTEM_PATHS ON)
set(BOOST_ROOT $ENV{REZ_BOOST_ROOT})
set(BOOST_INCLUDEDIR ${BOOST_ROOT}/include)
set(BOOST_LIBRARYDIR ${BOOST_ROOT}/lib)

find_package(Boost 1.73 REQUIRED COMPONENTS
    regex
    system
    filesystem
    thread
    date_time
    atomic
    python27
)

include_directories(
    ${Boost_INCLUDE_DIRS}
)

# TBB
find_package(TBB REQUIRED)

include_directories(
    ${TBB_INCLUDE_DIRS}
)

# Embree
find_package(embree 3.0 REQUIRED)

include_directories(
    ${EMBREE_INCLUDE_DIRS}
)

# USD
set(USD_ROOT $ENV{REZ_USD_ROOT})

find_package(USD REQUIRED)

set(USD_LIBS
    ${USD_LIBRARIES}
    ${Python_LIBRARIES}
    ${Boost_ATOMIC_LIBRARY}
    ${Boost_CHRONO_LIBRARY}
    ${Boost_DATE_TIME_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_PYTHON_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_REGEX_LIBRARY}
)

include_directories(
    ${USD_INCLUDE_DIRS}
)

# Qt
# find_package(Qt5 COMPONENTS
#     Core
#     Gui
#     Widgets
#     REQUIRED
# )

# set(QT_LIBS
#     Qt5::Core
#     Qt5::Gui
#     Qt5::Widgets
# )

# GLFW
find_package(glfw3 REQUIRED)

include_directories(${GLFW_INCLUDE_DIRS})

#############################
### Included dependencies ###
#############################

# GLAD
# add_library(glad "thirdparty/glad/src/glad.c")

# include_directories(
#     thirdparty/CLI11
#     thirdparty/embree/include
#     thirdparty/glad/include
#     thirdparty/glfw/include
#     thirdparty/spdlog
#     thirdparty/tinyexr
# )
