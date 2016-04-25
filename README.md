# QGCodeEditor

A Qt5 widget for editing gcode.

Based upon QPlainTextEdit, with added comment and syntax highlighting

plus line highlighting for use showing currently executing lin in a GUI.

To use clone and build with

`qmake -makefile`

`make`

Then copy the `libQGCodeEditorWidget.so` library to your Qt installation under

{QtInstallDir}/plugins/designer

Copy the header `QGcodeEditorPlugin.h` to a suitable include directory that is in your include path spec

(suggest your {QtInstallDir}/include)
