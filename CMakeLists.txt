cmake_minimum_required(VERSION 3.23)
project(pickpic)

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

add_executable(pickpic src/main.cpp src/mainwindow.cpp src/mainwindow.h ${MyResources} src/AppModel.cpp src/AppModel.h src/log.h)
target_link_libraries(pickpic
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

