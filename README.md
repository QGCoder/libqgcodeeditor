# QGCodeEditor

A Qt5 widget for editing G-Code.

Based upon QPlainTextEdit, with added comment and
syntax highlighting plus line highlighting for use
showing currently executing line in a GUI.

To use on Linux / Mac clone and build with:
```
git clone https://github.com/ArcEye/QGCodeEditor
cd QGCodeEditor
qmake PREFIX=/usr
make
sudo make install
```
To run one of the examples:
```
./examples/simple/simple
./examples/contextMenu/contextMenu
```

Or build and install as a Debian package (WIP):
```
git clone https://github.com/ArcEye/QGCodeEditor
cd QGCodeEditor
debuild -uc -us
sudo dpkg -i ../libgcode*deb
```
