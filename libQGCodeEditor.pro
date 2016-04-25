CONFIG       += ordered
TEMPLATE      = subdirs
SUBDIRS       = QGCodeEditor DesignerPlugin examples

QT_VERSION=$$[QT_VERSION]

contains( QT_VERSION, "^5.*" ) {
        cache()
}
