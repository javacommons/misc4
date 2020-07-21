QT += gui network widgets

CONFIG += c++11 console

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$PWD/../common

SOURCES += \
        main.cpp

copy_debug.commands = cmd -c $(COPY_DIR) $$shell_path($$PWD/dark.*) $$shell_path($$OUT_PWD/debug)
copy_release.commands = cmd -c $(COPY_DIR) $$shell_path($$PWD/dark.*) $$shell_path($$OUT_PWD/release)
QMAKE_EXTRA_TARGETS += copy_debug copy_release
