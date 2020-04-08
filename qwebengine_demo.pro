#-------------------------------------------------
#
# Project created by QtCreator 2020-03-30T09:31:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webchannel webenginewidgets multimedia multimediawidgets

TARGET = iTeach_ppss_Teacher
TEMPLATE = app
DESTDIR = ./bin

CONFIG(debug, debug|release) {
    DEFINES += QT_NO_DEBUG
}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

INCLUDEPATH += ./vote/include
LIBS += -L$$PWD/libs -lSunVoteSDK

win32{
LIBS += -lAdvapi32
LIBS += -ldbghelp
LIBS += -luser32
}

SOURCES += \
        JSBridgeBase.cpp \
        JSUIBridge.cpp \
        main.cpp \
        WebUI.cpp \
        vote/JSVoteBridge.cpp \
        vote/SunVoteManager.cpp

HEADERS += \
    JSBridgeBase.h \
    JSUIBridge.h \
    WebUI.h \
    vote/JSVoteBridge.h \
    vote/SunVoteManager.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES +=
