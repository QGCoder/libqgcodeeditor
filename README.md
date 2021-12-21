A [Qt5 designer widget plugin](https://doc.qt.io/qt-5/designer-creating-custom-widgets.html) for syntax highlighting and editing [G-code](https://en.wikipedia.org/wiki/G-code):

<img src="https://raw.githubusercontent.com/QGCoder/libqgcodeeditor/master/doc/libqgcodeeditor-designer-widget.png"/>

Based upon [QPlainTextEdit](https://doc.qt.io/qt-5/qplaintextedit.html), with added comment and syntax highlighting plus line highlighting for use showing currently executing line in a GUI.

To use on Windows/Linux/Mac clone and build with:
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

A benchmark can be found in [examples/pipe/](examples/pipe).

## Ubuntu/Debian packaging

To build and install libqgcodeeditor as an Ubuntu/Debian package, run:
```bash
gh repo clone QGCoder/libqgcodeeditor
cd libqgcodeeditor
sudo apt -y install -qq devscripts equivs lintian qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools
mk-build-deps -i -s sudo -t "apt --yes --no-install-recommends"
dpkg-buildpackage -b -rfakeroot -us -uc
sudo dpkg -i ../libqgcodeeditor*deb
```

-- Tested on Ubuntu 21.04.

## Authors

* [@ArcEye](https://github.com/ArcEye) - Initial version based on [QtMDI](https://github.com/unseenlaser/qtMDI).
* [@koppi](https://github.com/koppi) - Debian packaging.

