# This is the qmake file for the QGcodeEditor plugin for Qt Designer.

TEMPLATE = lib
TARGET = qgcodeeditorplugin

# Comment this in to build a dynamic library supporting multiple architectures
# on macOS.
#QMAKE_APPLE_DEVICE_ARCHS = x86_64 arm64

CONFIG += plugin qgcodeeditor debug

QT += designer

# Work around QTBUG-39300.
CONFIG -= android_install
greaterThan(QT_MAJOR_VERSION, 5) {
     LIBS += -lqgcodeeditor_qt6
} else {
     LIBS += -lqgcodeeditor_qt5
}

HEADERS = qgcodeeditorplugin.h
SOURCES = qgcodeeditorplugin.cpp

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target

INCLUDEPATH += ../src
