QT += gui network widgets

CONFIG += c++11 console

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$PWD/../common

SOURCES += \
        main.cpp

defineReplace(makeCopyCommand){
    DEPEND_FILE = $$1
    CONFIG(debug,debug|release){
        APP_BUILD_DIR=$${OUT_PWD}/debug
    }else{
        APP_BUILD_DIR=$${OUT_PWD}/release
    }
    return($(COPY_DIR) $$DEPEND_FILE $$APP_BUILD_DIR)
}

copy1.commands += $$makeCopyCommand($${PWD}/dark.*)
QMAKE_EXTRA_TARGETS += copy1
copy2.commands += $$makeCopyCommand($${PWD}/*.dll)
QMAKE_EXTRA_TARGETS += copy2
