#-------------------------------------------------
#
# Project created by QtCreator 2016-12-28T14:28:51
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = doveMailAdmin
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/dialog_addserver.cpp \
    src/dialog_domains.cpp \
    src/dialog_users.cpp \
    src/dialog_domains_add.cpp \
    src/dialog_changepassword.cpp \
    src/qssha256.cpp \
    src/dialog_users_add.cpp \
    src/dialog_users_addforwarding.cpp

HEADERS  += src/mainwindow.h \
    src/dialog_addserver.h \
    src/dialog_domains.h \
    src/dialog_users.h \
    src/serverparams.h \
    src/dialog_domains_add.h \
    src/dialog_changepassword.h \
    src/qssha256.h \
    src/dialog_users_add.h \
    src/dialog_users_addforwarding.h

FORMS    += src/mainwindow.ui \
    src/dialog_addserver.ui \
    src/dialog_domains.ui \
    src/dialog_users.ui \
    src/dialog_domains_add.ui \
    src/dialog_changepassword.ui \
    src/dialog_users_add.ui \
    src/dialog_users_addforwarding.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    resources.qrc

DISTFILES += \
    EXTERNAL_LICENCES \
    LICENSE \
    README.md

