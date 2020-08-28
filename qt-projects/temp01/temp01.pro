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

HEADERS += \
    ../common/qtcommon.hpp

DISTFILES += \
    post.sh

defineReplace(makeBashCommand){
    DEPEND_FILE = $$1
    CONFIG(debug,debug|release){
        APP_BUILD_DIR=$${OUT_PWD}/debug
    }else{
        APP_BUILD_DIR=$${OUT_PWD}/release
    }
    return(env SRC_DIR=$${PWD} BLD_DIR=$${APP_BUILD_DIR} bash $$DEPEND_FILE)
}

post.commands += $$makeBashCommand($${PWD}/post.sh)
QMAKE_EXTRA_TARGETS += post
