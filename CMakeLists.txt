cmake_minimum_required(VERSION 3.23)
project(picpicker)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

QT5_ADD_RESOURCES(MyResources application.qrc)

add_executable(picpicker
        src/main.cpp
        src/mainwindow.cpp
        ${MyResources}
        src/AppModel.cpp
        )
target_link_libraries(picpicker
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

