TEMPLATE = app
TARGET = nonogram-qt
DEPENDPATH += .
INCLUDEPATH += .
QT += core gui widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Input
HEADERS += linesolver.h mainwindow.h nonogram.h pushbutton.h solver.h
SOURCES += linesolver.cpp \
           main.cpp \
           mainwindow.cpp \
           nonogram.cpp \
           pushbutton.cpp \
           solver.cpp
TRANSLATIONS += translations/nonogram_sv.ts translations/nonogram_fi.ts translations/nonogram_ko.ts
RESOURCES += nonogram-qt.qrc

FORMS += \
    dialog.ui
CONFIG+=lrelease
