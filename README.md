A [Qt5 designer widget plugin](https://doc.qt.io/qt-5/designer-creating-custom-widgets.html) for syntax highlighting and editing [G-code](https://en.wikipedia.org/wiki/G-code):

<img src="https://raw.githubusercontent.com/QGCoder/libqgcodeeditor/main/doc/libqgcodeeditor-designer-widget.png"/>

[![C/C++ CI](https://github.com/QGCoder/libqgcodeeditor/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/QGCoder/libqgcodeeditor/actions/workflows/c-cpp.yml)

Based upon [QPlainTextEdit](https://doc.qt.io/qt-5/qplaintextedit.html), with added comment and syntax highlighting plus line highlighting for use showing currently executing line in a GUI.

To use clone and build with:
```bash
gh repo clone QGCoder/libqgcodeeditor && cd libqgcodeeditor
qmake && make -j$(nproc)
sudo make install
```

To run one of the examples:
```bash
cd examples
qmake && make
./simple/simple
./contextMenu/contextMenu
```

A benchmark can be found in [examples/pipe/](examples/pipe).

## Authors

* **ArcEye** – [ArcEye](https://github.com/ArcEye) - Initial version based on [QtMDI](https://github.com/unseenlaser/qtMDI).
* **Jakob Flierl** – [koppi](https://github.com/koppi) - Ubuntu / Debian packaging.

