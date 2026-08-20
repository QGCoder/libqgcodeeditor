cmake_minimum_required(VERSION 3.16)

project(libqgcodeeditor
    VERSION 0.1.23
    DESCRIPTION "Qt 5 / Qt 6 G-code editor widget based on QPlainTextEdit"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

include(GNUInstallDirs)

set(QGCODEEDITOR_INSTALL_INCLUDEDIR "${CMAKE_INSTALL_INCLUDEDIR}/QGCodeEditor"
    CACHE STRING "Directory where the QGCodeEditor headers are installed")

option(BUILD_STATIC_LIB "Build a static library instead of a shared one" OFF)
option(BUILD_EXAMPLES "Build the examples" ON)
option(BUILD_DESIGNER_PLUGIN "Build the Qt Designer plugin" ON)

if(NOT DEFINED QT_VERSION_MAJOR)
    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
endif()
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(QGCODEEDITOR_TARGET qgcodeeditor_qt${QT_VERSION_MAJOR})

set(QGCODEEDITOR_STAGE_DIR "${CMAKE_CURRENT_BINARY_DIR}/QGCodeEditor")
file(MAKE_DIRECTORY "${QGCODEEDITOR_STAGE_DIR}")
file(COPY
    src/QGCodeEditor.h
    src/QGCodeSyntaxHighlighter.h
    DESTINATION "${QGCODEEDITOR_STAGE_DIR}")

if(BUILD_STATIC_LIB)
    set(QGCODEEDITOR_LIB_TYPE STATIC)
else()
    set(QGCODEEDITOR_LIB_TYPE SHARED)
endif()

add_library(${QGCODEEDITOR_TARGET} ${QGCODEEDITOR_LIB_TYPE}
    src/QGCodeEditor.cpp
    src/QGCodeEditor.h
    src/QGCodeSyntaxHighlighter.cpp
    src/QGCodeSyntaxHighlighter.h)
add_library(QGCodeEditor::QGCodeEditor ALIAS ${QGCODEEDITOR_TARGET})

get_filename_component(_QGCODEEDITOR_INSTALL_INCLUDE_PARENT
    "${QGCODEEDITOR_INSTALL_INCLUDEDIR}" DIRECTORY)

target_include_directories(${QGCODEEDITOR_TARGET}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:${_QGCODEEDITOR_INSTALL_INCLUDE_PARENT}>)

target_link_libraries(${QGCODEEDITOR_TARGET}
    PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(${QGCODEEDITOR_TARGET} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR})

if(BUILD_EXAMPLES)
    add_executable(simple
        examples/simple/main.cpp
        examples/simple/mainwindow.cpp
        examples/simple/mainwindow.h
        examples/simple/mainwindow.ui)
    target_include_directories(simple PRIVATE examples/simple)
    target_link_libraries(simple PRIVATE QGCodeEditor::QGCodeEditor)

    add_executable(contextMenu
        examples/contextMenu/main.cpp
        examples/contextMenu/mainwindow.cpp
        examples/contextMenu/mainwindow.h
        examples/contextMenu/mainwindow.ui
        examples/contextMenu/mygcodeeditor.cpp
        examples/contextMenu/mygcodeeditor.h)
    target_include_directories(contextMenu PRIVATE examples/contextMenu)
    target_link_libraries(contextMenu PRIVATE QGCodeEditor::QGCodeEditor)

    add_executable(pipe
        examples/pipe/main.cpp
        examples/pipe/mainwindow.cpp
        examples/pipe/mainwindow.h
        examples/pipe/mainwindow.ui
        examples/pipe/mygcodeeditor.cpp
        examples/pipe/mygcodeeditor.h)
    target_include_directories(pipe PRIVATE examples/pipe)
    target_link_libraries(pipe PRIVATE QGCodeEditor::QGCodeEditor)
endif()

if(BUILD_DESIGNER_PLUGIN)
    find_package(Qt${QT_VERSION_MAJOR}Designer QUIET)
    find_package(Qt${QT_VERSION_MAJOR}UiPlugin QUIET)
    if(TARGET Qt${QT_VERSION_MAJOR}::UiPlugin)
        add_library(qgcodeeditorplugin MODULE
            designer/QGCodeEditorPlugin.cpp
            designer/QGCodeEditorPlugin.h)
        target_include_directories(qgcodeeditorplugin PRIVATE src)
        target_link_libraries(qgcodeeditorplugin PRIVATE
            QGCodeEditor::QGCodeEditor
            Qt${QT_VERSION_MAJOR}::Widgets
            Qt${QT_VERSION_MAJOR}::UiPlugin)

        if(DEFINED QT${QT_VERSION_MAJOR}_INSTALL_PLUGINS)
            set(QT_DESIGNER_PLUGIN_DIR "${QT${QT_VERSION_MAJOR}_INSTALL_PLUGINS}/designer")
        elseif(QT_VERSION_MAJOR EQUAL 6)
            set(QT_DESIGNER_PLUGIN_DIR "${CMAKE_INSTALL_LIBDIR}/qt6/plugins/designer")
        else()
            set(QT_DESIGNER_PLUGIN_DIR "${CMAKE_INSTALL_LIBDIR}/qt5/plugins/designer")
        endif()

        install(TARGETS qgcodeeditorplugin
            LIBRARY DESTINATION ${QT_DESIGNER_PLUGIN_DIR})
    else()
        message(WARNING "Qt Designer / UiPlugin not found. Skipping the designer plugin.")
    endif()
endif()

install(TARGETS ${QGCODEEDITOR_TARGET}
    EXPORT QGCodeEditorTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES
    src/QGCodeEditor.h
    src/QGCodeSyntaxHighlighter.h
    DESTINATION ${QGCODEEDITOR_INSTALL_INCLUDEDIR})
install(EXPORT QGCodeEditorTargets
    FILE QGCodeEditorTargets.cmake
    NAMESPACE QGCodeEditor::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QGCodeEditor)
