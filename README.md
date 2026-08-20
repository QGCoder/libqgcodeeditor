A [Qt 5 / Qt 6 designer widget plugin](https://doc.qt.io/qt-5/designer-creating-custom-widgets.html) for syntax highlighting and editing [G-code](https://en.wikipedia.org/wiki/G-code):

<img src="https://raw.githubusercontent.com/QGCoder/libqgcodeeditor/main/doc/libqgcodeeditor-designer-widget.png"/>

[![C/C++ CI](https://github.com/QGCoder/libqgcodeeditor/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/QGCoder/libqgcodeeditor/actions/workflows/c-cpp.yml)

Based upon [QPlainTextEdit](https://doc.qt.io/qt-5/qplaintextedit.html), with added comment and syntax highlighting plus line highlighting for use showing currently executing line in a GUI.

### CMake build

To clone and build with CMake:
```bash
gh repo clone QGCoder/libqgcodeeditor && cd libqgcodeeditor
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
sudo make install
```

#### CMake options

| Option | Default | Description |
|---|---|---|
| `BUILD_STATIC_LIB` | `OFF` | Build a static library instead of shared |
| `BUILD_EXAMPLES` | `ON` | Build example executables |
| `BUILD_DESIGNER_PLUGIN` | `ON` | Build the Qt Designer plugin |
| `QT_VERSION_MAJOR` | auto-detected | Set to `5` or `6` to force a specific Qt version |

Example with options:
```bash
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_STATIC_LIB=ON -DQT_VERSION_MAJOR=6
```

### Running the examples

After building (both CMake and qmake):
```bash
cd examples
./simple/simple
./contextMenu/contextMenu
```

A benchmark can be found in [examples/pipe/](examples/pipe).

## Authors

* **ArcEye** – [ArcEye](https://github.com/ArcEye) - Initial version based on [QtMDI](https://github.com/unseenlaser/qtMDI).
* **Jakob Flierl** – [koppi](https://github.com/koppi) - Ubuntu / Debian packaging.

