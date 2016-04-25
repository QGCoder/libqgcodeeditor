# QGCodeEditor

A Qt5 widget for editing gcode.

Based upon QPlainTextEdit, with added comment and syntax highlighting

plus line highlighting for use showing currently executing line in a GUI.

To use clone and build with

`qmake -makefile`

`make`

Then copy the `libQGCodeEditor.so` library to your Qt installation under {QtInstallDir}/plugins/designer

( with a symlink to /usr/local/lib/libQGCodeEditor.so if your designer plugins are not in your LIBPATH )


Copy the header `QGCodeEditor.h` to a suitable include directory that is in your include path spec

(suggest your {QtInstallDir}/include)
