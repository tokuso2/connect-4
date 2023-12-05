QT += core widgets gui

SOURCES += main.cpp \
            mainwindow.cpp \
            connect4widget.cpp
HEADERS += mainwindow.h \
            connect4widget.h
# FORMS += dials.ui

# install
target.path = ./
INSTALLS += target
