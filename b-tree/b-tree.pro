TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    btreeitem.cpp \
    noncopyable.cpp \
    btreenode.cpp \
    container.cpp \
    vectorcontainer.cpp

HEADERS += \
    btreeitem.h \
    noncopyable.h \
    btreenode.h \
    container.h \
    vectorcontainer.h
