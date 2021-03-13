find_package(Qt5 COMPONENTS
    Core
    Gui
    Widgets
    REQUIRED
)

set(QT_LIBRARIES
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
