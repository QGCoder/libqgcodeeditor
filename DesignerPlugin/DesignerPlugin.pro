TEMPLATE = lib

TARGET   = qgcodeeditorplugin
CONFIG  *= warn_on plugin dll

INCLUDEPATH += ../QGCodeEditor
DEPENDPATH  += ../QGCodeEditor

LIBS  += -L ../QGCodeEditor -lQGCodeEditor

QMAKE_CFLAGS_RELEASE -= -g
QMAKE_CXXFLAGS_RELEASE -= -g

QT_VERSION=$$[QT_VERSION]

message(Plugins: $$[QT_INSTALL_PLUGINS])

PREFIX=$$[QT_INSTALL_PLUGINS]

target.path = $${PREFIX}/designer
INSTALLS += target

HEADERS = QGCodeEditorPlugin.h   QGCodeEditorWidget.h
SOURCES = QGCodeEditorPlugin.cpp QGCodeEditorWidget.cpp

contains( QT_VERSION, "^5.*" ) {
  QT *= designer
  CONFIG *= release
  OTHER_FILES += designerplugindescription.json
} else {
  contains( QT_VERSION, "^4.*" ) {
    CONFIG *= designer release
  } else {
    HEADERS = qgcodeeditorPlugin.Qt3.h    // as of 2016 Qt3 is deprectated
    SOURCES = qgcodeeditorPlugin.Qt3.cpp  // add these two files for Qt3 if needed
  }
}

greaterThan(QT_MAJOR_VERSION,4):greaterThan(QT_MINOR_VERSION,4) {
  QT *= uiplugin
}
