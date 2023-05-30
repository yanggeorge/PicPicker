QT += widgets core gui

ICON = AppIcon.icns

CONFIG += c++11

SOURCES += src/main.cpp src/mainwindow.cpp src/AppModel.cpp

HEADERS += src/AppModel.h src/mainwindow.h src/log.h

RESOURCES += application.qrc

TARGET = pickpic
