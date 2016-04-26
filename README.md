# QGCodeEditor

[![Build Status](https://api.travis-ci.org/koppi/QGCodeEditor.svg?branch=master)](https://travis-ci.org/koppi/GCodeEditor) [![Join the chat at https://gitter.im/koppi/QGCodeEditor](https://badges.gitter.im/koppi/QGCodeEditor.svg)](https://gitter.im/koppi/QGCodeEditor?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

A Qt5 widget for editing G-Code.

Based upon QPlainTextEdit, with added comment and
syntax highlighting plus line highlighting for use
showing currently executing line in a GUI.

To use on Linux / Mac clone and build with:
```
git clone https://github.com/ArcEye/QGCodeEditor
cd QGCodeEditor
qmake
make
sudo make install
```
To run one of the examples:
```
cd examples
make
simple/simple
contextMenu/contextMenu
```

Or build and install as a Debian package (WIP):
```
git clone https://github.com/ArcEye/QGCodeEditor
cd QGCodeEditor
dpkg-buildpackage -b -rfakeroot -us -uc
sudo dpkg -i ../libqgcodeeditor*deb
```
