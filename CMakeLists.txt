cmake_minimum_required(VERSION 3.23)
project(picpicker)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
# for *.ui to include current dir to find headers.
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Xml
        REQUIRED)

set(SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/AppModel.cpp
        )

set(l10n_files
        )

QT5_ADD_RESOURCES(MyResources application.qrc)

set(MACOSX_BUNDLE_ICON_FILE AppIcon.icns)
set(app_icon_macos "${CMAKE_SOURCE_DIR}/AppIcon.icns")
set_source_files_properties(${app_icon_macos} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
set_source_files_properties(${l10n_files} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources/l10n")

add_executable(PicPicker
        ${SOURCES}
        ${MyResources}
        ${app_icon_macos}
        ${l10n_files}
        )

set_target_properties(PicPicker PROPERTIES
        MACOSX_BUNDLE TRUE
        )

target_link_libraries(PicPicker
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Xml
        )

# cmake -DDEPLOY=1  ..
if (DEFINED DEPLOY)
    message("to execute macdeployqt")
    get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
    get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
    find_program(MACDEPLOYQT_EXECUTABLE macdeployqt HINTS "${_qt_bin_dir}")

    add_custom_command(TARGET PicPicker POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_CURRENT_SOURCE_DIR}/AppIcon.icns"
            "$<TARGET_FILE_DIR:PicPicker>/../Resources/"
            COMMENT "Copy AppIcon.icns to Resources/"
            &&
            COMMAND "${MACDEPLOYQT_EXECUTABLE}"
            ARGS "PicPicker.app" "-dmg" "-always-overwrite" "-no-strip"
            COMMENT "Execute macdeployqt to create macOS bundle"
            )
endif ()

# here is a bug, this custom command always executes before copying icns to resources.
#        [100%] Linking CXX executable PicPicker.app/Contents/MacOS/PicPicker
#        Execute macdeployqt to create macOS bundle
#        Copying OS X content PicPicker.app/Contents/Resources/AppIcon.icns
#        [100%] Built target PicPicker
#   alternative method is running below on shell
#           macdeployqt PicPicker.app  -dmg -always-overwrite
# https://riptutorial.com/qt/example/24133/integrating-with-cmake
#find_program(MACDEPLOYQT_EXECUTABLE macdeployqt HINTS "${_qt_bin_dir}")
#add_custom_command(TARGET PicPicker POST_BUILD
#        COMMAND "${MACDEPLOYQT_EXECUTABLE}"
#        ARGS "PicPicker.app" "-dmg" "-always-overwrite"
#        COMMENT "Execute macdeployqt to create macOS bundle")