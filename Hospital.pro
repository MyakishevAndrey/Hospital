#-------------------------------------------------
#
# Project created by QtCreator 2016-10-09T10:16:46
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Hospital
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    doctor.cpp \
    workerreg.cpp \
    manager.cpp

HEADERS  += dialog.h \
    doctor.h \
    workerreg.h \
    manager.h

FORMS    += dialog.ui \
    doctor.ui \
    workerreg.ui \
    manager.ui
