#-------------------------------------------------
#
# Project created by QtCreator 2017-05-19T21:26:20
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyTalk
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        loginpage.cpp \
    registerpage.cpp \
    talkpage.cpp \
    addfriendpage.cpp \
    mydescpage.cpp \
    showresultpage.cpp \
    mibao.cpp \
    database.cpp \
    xiugmm.cpp

HEADERS  += loginpage.h \
    registerpage.h \
    talkpage.h \
    addfriendpage.h \
    mydescpage.h \
    showresultpage.h \
    protocal.h \
    mibao.h \
    database.h \
    xiugmm.h

FORMS    += loginpage.ui \
    registerpage.ui \
    talkpage.ui \
    addfriendpage.ui \
    mydescpage.ui \
    showresultpage.ui \
    mibao.ui \
    xiugmm.ui
