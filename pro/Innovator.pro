QT -= gui

QMAKE_LFLAGS += -no-pie

CONFIG += c++11 console
CONFIG -= app_bundle
# 添加对C++11的支持
CONFIG += C++11

CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lpthread \
        -lX11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#添加头文件路径
INCLUDEPATH += /usr/include/opencv4

LIBS += -L/usr/lib/aarch64-linux-gnu -lopencv_core -lopencv_imgcodecs  -lopencv_imgproc -lopencv_highgui -lopencv_objdetect -lopencv_ml -lopencv_video -lopencv_videoio  -lopencv_calib3d -lopencv_dnn -lopencv_features2d -lopencv_flann -lopencv_photo -lopencv_stitching
# -lopencv_gxiapi
SOURCES += main.cpp \
    serial_innovator.cpp \
    angle_solver.cpp \
    color_identify.cpp \
    qrcode.cpp \
    relative_position_identifyy.cpp

HEADERS += \
    serial_innovator.h \
    headers.h

unix:!macx: LIBS += -L$$PWD/../../../../usr/lib/aarch64-linux-gnu/ -lzbar

INCLUDEPATH += $$PWD/../../../../usr/lib/aarch64-linux-gnu
DEPENDPATH += $$PWD/../../../../usr/lib/aarch64-linux-gnu
