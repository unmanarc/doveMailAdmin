#-------------------------------------------------
#
# Project created by QtCreator 2016-12-28T14:28:51
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = doveMailAdmin
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog_addserver.cpp \
    dialog_domains.cpp \
    dialog_users.cpp \
    dialog_domains_add.cpp \
    dialog_changepassword.cpp \
    qssha256.cpp \
    dialog_users_add.cpp \
    dialog_users_addforwarding.cpp

HEADERS  += mainwindow.h \
    dialog_addserver.h \
    dialog_domains.h \
    dialog_users.h \
    serverparams.h \
    dialog_domains_add.h \
    dialog_changepassword.h \
    qssha256.h \
    dialog_users_add.h \
    dialog_users_addforwarding.h

FORMS    += mainwindow.ui \
    dialog_addserver.ui \
    dialog_domains.ui \
    dialog_users.ui \
    dialog_domains_add.ui \
    dialog_changepassword.ui \
    dialog_users_add.ui \
    dialog_users_addforwarding.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    resources.qrc

DISTFILES += \
    EXTERNAL_LICENCES \
    LICENSE

