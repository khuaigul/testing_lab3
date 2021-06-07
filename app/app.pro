TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt

# gcov
QMAKE_CFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov

SOURCES += \
    main.cpp \
    mwindow.cpp

HEADERS += \
    mwindow.h

QMAKE_CFLAGS += -Wall -Wextra -Werror


