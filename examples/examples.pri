QT *= widgets gui

CONFIG += qt warn_on thread rtti console embed_manifest_exe

# Uncomment and tune these paths according to your configuration.

#INCLUDEPATH *=   C:/Users/ArcEye/Documents/libQGCodeEditor-VERSION
#LIBS        *= -LC:/Users/ArcEye/Documents/libQGCodeEditor-VERSION/QGCodeEditor -lQGCodeEditor

# --------------------------------------------------------------------------------------

# The rest of this file sets these paths so that the examples
# can be compiled out of the box

ROOT_DIRECTORY = ../..

contains( _PRO_FILE_PWD_, ".*designerPlugin$" ) {
	ROOT_DIRECTORY = ..
}
contains( _PRO_FILE_PWD_, ".*/contribs/.+/.+" ) {
	ROOT_DIRECTORY = ../../../..
} else {	
	contains( _PRO_FILE_PWD_, ".*/contribs/.+" ) {
		ROOT_DIRECTORY = ../../..
	}
}

INCLUDE_DIR = $${ROOT_DIRECTORY}
LIB_DIR = $${ROOT_DIRECTORY}/QGCodeEditor

# Include path, taking QGCodeEditor path prefix into account
INCLUDEPATH *= $${INCLUDE_DIR}
DEPENDPATH  *= $${INCLUDE_DIR}

unix {
	CONFIG -= debug debug_and_release
	CONFIG *= release

	isEmpty( QGCODEEDITOR_STATIC ) {
		# The absolute path where the library or framework was found
		LIB_DIR_ABSOLUTE_PATH = $$dirname(PWD)/QGCodeEditor
		
		macx|darwin-g++ {
			# Use install_name_tool to set the absolute path of the lib in the executable
			exists( $${LIB_DIR_ABSOLUTE_PATH}/QGCodeEditor.framework ) {
				!plugin:QMAKE_POST_LINK=install_name_tool -change QGCodeEditor.framework/Versions/2/QGCodeEditor $${LIB_DIR_ABSOLUTE_PATH}/QGCodeEditor.framework/Versions/2/QGCodeEditor $${TARGET}.app/Contents/MacOS/$${TARGET} #VERSION_MAJOR
				LIBS += -F$${LIB_DIR_ABSOLUTE_PATH} -framework QGCodeEditor
			} else {
				!plugin:QMAKE_POST_LINK=install_name_tool -change libQGCodeEditor.2.dylib $${LIB_DIR_ABSOLUTE_PATH}/libQGCodeEditor.2.dylib $${TARGET}.app/Contents/MacOS/$${TARGET} #VERSION_MAJOR
				LIBS *= -L$${LIB_DIR} -lQGCodeEditor
			}
		} else {
			isEmpty(QMAKE_LFLAGS_RPATH) {
				!plugin:QMAKE_LFLAGS += -Wl,-rpath,$${LIB_DIR_ABSOLUTE_PATH}
			} else {
				!plugin:QMAKE_RPATHDIR *= $${LIB_DIR_ABSOLUTE_PATH}
			}
			LIBS *= -L$${LIB_DIR} -lQGCodeEditor
		}
	} else {
		LIBS *= $${LIB_DIR}/libQGCodeEditor.a
	}

	# Intermediate files are created in hidden folders
	MOC_DIR = .moc
	OBJECTS_DIR = .obj
}


win32 {
	CONFIG *= debug_and_release

	# Seems to be needed for Visual Studio with Intel compiler
	DEFINES *= WIN32

	isEmpty( QGCODEEDITOR_STATIC ) {
		LIBS *= -L$${LIB_DIR} -lQGCodeEditor
	} else {
		DEFINES *= QGCODEEDITOR_STATIC
		LIBS *= $${LIB_DIR}/libQGCodeEditor.a
	}
}

# Application icon
macx|darwin-g++ {
	ICON = $${ROOT_DIRECTORY}/QGCodeEditor/qgcodeeditor.icns
}

win32 {
	!designer {
		exists( $${ROOT_DIRECTORY}/examples/qgcodeeditor.rc ) {
			RC_FILE = $${ROOT_DIRECTORY}/examples/qgcodeeditor.rc
		}
	}
}
