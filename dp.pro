QT       += core gui widgets
TRANSLATIONS = dp_cn.ts \
                dp_en.ts

TARGET = doublePendulumn
TEMPLATE = app

SOURCES += main.cpp \
    ball.cpp \
    line.cpp \
    func.cpp \
    dpendulum.cpp \
    mainwindow.cpp

SOURCES += \
    mainwidget.cpp

INCLUDEPATH+=D:\gsl-2.2.1_mingw-6.2.0\gsl-2.2.1-static\include

HEADERS += \
    mainwidget.h \
    ball.h \
    line.h \
    dpendulum.h \
    func.h \
    mainwindow.h

RESOURCES += \
    shaders.qrc \
    textures.qrc \
    trans.qrc

LIBS+=-LD:\gsl-2.2.1_mingw-6.2.0\gsl-2.2.1-static\lib -lgsl -lgslcblas -lm
# install
#target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
#INSTALLS += target

