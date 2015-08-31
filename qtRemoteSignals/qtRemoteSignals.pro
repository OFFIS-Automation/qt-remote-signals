QT       += core


CONFIG   += console
CONFIG   -= app_bundle
DESTDIR = $${PWD}/../bin

TEMPLATE = app
CONFIG(debug, debug|release) {
    TARGET = qtRemoteSignalsd
} else {
    TARGET = qtRemoteSignals
}




SOURCES += src/main.cpp \
    ../bin/RemoteSignals.cpp \
    src/ConfigFileReader.cpp \
    src/Method.cpp \
    src/BaseClassWriter.cpp \
    src/UserClassWriter.cpp

HEADERS += \
    ../bin/RemoteSignals.h \
    src/ConfigFileReader.h \
    src/Method.h \
    src/Parameter.h \
    src/BaseClassWriter.h \
    src/UserClassWriter.h

dlls.path  =  $${DESTDIR}
dllA.path   += $${DESTDIR}/platforms
dllB.path   += $${DESTDIR}/plugins/imageformats/

CONFIG(debug, debug|release) {
    dlls.files += $$[QT_INSTALL_BINS]/icudt5*.dll
    dlls.files += $$[QT_INSTALL_BINS]/icuin5*.dll
    dlls.files += $$[QT_INSTALL_BINS]/icuuc5*.dll
    dlls.files += $$[QT_INSTALL_BINS]/Qt5Cored.dll
    dlls.files += $$[QT_INSTALL_BINS]/Qt5Networkd.dll
    dlls.files += $$[QT_INSTALL_BINS]/Qt5Guid.dll
    dlls.files += $$[QT_INSTALL_BINS]/Qt5Widgetsd.dll
    dlls.files += $$[QT_INSTALL_BINS]/Qt5PrintSupportd.dll
    dlls.files += $$[QT_INSTALL_BINS]/Qt5Widgetsd.dll
} else {
    dlls.files += $$[QT_INSTALL_BINS]/icudt5*.dll
    dlls.files += $$[QT_INSTALL_BINS]/icuin5*.dll
    dlls.files += $$[QT_INSTALL_BINS]/icuuc5*.dll
    dlls.files += $$[QT_INSTALL_BINS]/Qt5Core.dll
    dlls.files += $$[QT_INSTALL_BINS]/Qt5Network.dll
    dlls.files += $$[QT_INSTALL_BINS]/Qt5Gui.dll
    dlls.files += $$[QT_INSTALL_BINS]/Qt5Widgets.dll
    dlls.files += $$[QT_INSTALL_BINS]/Qt5PrintSupport.dll
}
dllA.files  += $$[QT_INSTALL_PLUGINS]/platforms/qwindows.dll
dllB.files  += $$[QT_INSTALL_PLUGINS]/imageformats/qico.dll
dllB.files  += $$[QT_INSTALL_PLUGINS]/imageformats/qwbmp.dll
INSTALLS   += dlls dllA dllB
