set(Python_ROOT_DIR $ENV{REZ_PYTHON_ROOT})

find_package(Python 3.10 REQUIRED Interpreter Development)

include_directories(
    ${Python_INCLUDE_DIRS}
)
