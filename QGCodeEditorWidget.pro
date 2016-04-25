CONFIG   += plugin release
TARGET   = $$qtLibraryTarget(QGCodeEditorWidget)
TEMPLATE = lib

HEADERS  = QGCodeEditorPlugin.h QGCodeEditorWidget.h

SOURCES  = QGCodeEditorPlugin.cpp QGCodeEditorWidget.cpp
		
LIBS     += -L. 

QT += designer

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target

SOURCES += QGCodeEditor.cpp comment_highlighter.cpp
