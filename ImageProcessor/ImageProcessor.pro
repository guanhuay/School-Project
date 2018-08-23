#-------------------------------------------------
#
# Project created by QtCreator 2017-01-24T14:51:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageProcessor
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
        mainwindow.cpp

FORMS    += mainwindow.ui

INCLUDEPATH+=C:/contrib/install/include/opencv \
             C:/contrib/install/include/opencv2 \
             C:/contrib/install/include

CONFIG(debug,debug|release) {
LIBS += -LC:/contrib/install/x64/vc14/lib \
    -lopencv_core310d \
    -lopencv_highgui310d \
    -lopencv_imgproc310d \
    -lopencv_features2d310d \
    -lopencv_calib3d310d \
    -lopencv_flann310d \
    -lopencv_imgcodecs310d \
    -lopencv_imgproc310d \
    -lopencv_ml310d \
    -lopencv_objdetect310d \
    -lopencv_photo310d \
    -lopencv_shape310d \
    -lopencv_stitching310d \
    -lopencv_superres310d \
    -lopencv_ts310d
} else:CONFIG(release, debug|release):{
LIBS += -LC:/contrib/install/x64/vc14/lib \
    -lopencv_core310 \
    -lopencv_highgui310 \
    -lopencv_imgproc310 \
    -lopencv_features2d310 \
    -lopencv_calib3d310 \
    -lopencv_imgcodecs310 \
    -lopencv_stitching310 \
    -lopencv_shape310 \
    -lopencv_flann310
}

HEADERS += \
    mainwindow.h
