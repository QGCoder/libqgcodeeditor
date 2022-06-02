# Run "qmake; make; make install" to compile and install the library on Unix systems.

TEMPLATE = lib
TARGET = QGCodeEditor
VERSION  = 0.1.0

QT      *= gui widgets

CONFIG  *= qt warn_on shared thread create_prl rtti

HEADERS = QGCodeEditor.h   QGCodeSyntaxHighlighter.h
SOURCES = QGCodeEditor.cpp QGCodeSyntaxHighlighter.cpp

DISTFILES *= qgcodeeditor-icon.xpm
DESTDIR  = $${PWD}

!isEmpty( QGCODEEDITOR_STATIC ) {
  CONFIG *= staticlib
}

unix {
        CONFIG -= debug debug_and_release
        CONFIG *= release

	# INCLUDE_DIR and LIB_DIR specify where to install the include files and the library.
	# Use qmake INCLUDE_DIR=... LIB_DIR=... , or qmake PREFIX=... to customize your installation.
        isEmpty( PREFIX ) {
                PREFIX_=/usr/local
        } else {
                PREFIX_=$${PREFIX}
        }
        isEmpty( LIB_DIR ) {
                LIB_DIR_ = $${PREFIX_}/lib
        } else {
                LIB_DIR_ = $${LIB_DIR}
        }
        isEmpty( INCLUDE_DIR ) {
                INCLUDE_DIR_ = $${PREFIX_}/include
        } else {
                INCLUDE_DIR_ = $${INCLUDE_DIR}
        }
        isEmpty( DOC_DIR ) {
                macx|darwin-g++ {
                        isEmpty( PREFIX ) {
                                DOC_DIR = $${PWD}/Library/Developer/Shared/Documentation/QGCodeEditor
                        } else {
                                DOC_DIR = $${PREFIX}/Shared/Documentation/QGCodeEditor
                        }
                } else {
                        DOC_DIR = $${PREFIX_}/share/doc/QGCodeEditor
                }
        }

        MOC_DIR = .moc
        OBJECTS_DIR = .obj

        # Adds a -P option so that "make install" as root creates files owned by root and links are preserved.
        # This is not a standard option, and it may have to be removed on old Unix flavors.
        !hpux {
                QMAKE_COPY_FILE = $${QMAKE_COPY_FILE} -P
        }

        # Make much smaller libraries (and packages) by removing debugging informations
        QMAKE_CFLAGS_RELEASE -= -g
        QMAKE_CXXFLAGS_RELEASE -= -g

        # install header
        include.path = $${INCLUDE_DIR_}/QGCodeEditor
        include.files = $${HEADERS}

        # install static library
        staticlib.extra = make -f Makefile.Release staticlib
        staticlib.path = $${LIB_DIR_}
        staticlib.files = lib$${TARGET}.a

        # install library
        target.path = $${LIB_DIR_}

	greaterThan(QT_MAJOR_VERSION, 4) {
    		features.path = $$[QT_HOST_DATA]/mkspecs/features
	} else {
		features.path = $$[QT_INSTALL_DATA]/mkspecs/features
	}
	features.files = $$PWD/features/qgcodeeditor.prf

        # "make install" configuration options
        INSTALLS *= target include features
}

# -------------------
# --  M a c O S X  --
# -------------------
macx|darwin-g++ {
        # This setting creates a Mac framework. Comment out this line to create a dylib instead.
        !staticlib: CONFIG *= lib_bundle

# TODO

}

build_pass:CONFIG(debug, debug|release) {
  unix: TARGET = $$join(TARGET,,,_debug)
  else: TARGET = $$join(TARGET,,,d)
}
