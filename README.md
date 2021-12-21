# QGCodeEditor [![Join the chat at https://gitter.im/QGCoder/QGCodeEditor](https://badges.gitter.im/QGCoder/QGCodeEditor.svg)](https://gitter.im/QGCoder/QGCodeEditor?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

A Qt5 widget plugin for editing gcode.

Based upon QPlainTextEdit, with added comment and
syntax highlighting plus line highlighting for use
showing currently executing line in a GUI.

To use on Linux/Mac clone and build with:
```bash
gh repo clone QGCoder/libqgcodeeditor
cd libqgcodeeditor
qmake
make
sudo make install
```
To run one of the examples:
```bash
cd examples
qmake
make
./simple/simple
./contextMenu/contextMenu
```

Or build and install as a Debian package:
```bash
gh repo clone QGCoder/libqgcodeeditor
cd libqgcodeeditor
sudo apt -y install -qq devscripts equivs lintian qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools
mk-build-deps -i -s sudo -t "apt --yes --no-install-recommends"
dpkg-buildpackage -b -rfakeroot -us -uc
sudo dpkg -i ../libqgcodeeditor*deb
```

## Authors

* [@ArcEye](https://github.com/ArcEye) - Initial version based on [QtMDI](https://github.com/unseenlaser/qtMDI).
* [@koppi](https://github.com/koppi) - Debian packaging.

