QT       += core gui
QT       += charts  #二维图像绘制
QT       += serialport      #串口
QT       += network
QT       +=  sql network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
INCLUDEPATH += /home/zhengbo/Desktop/opencv/install/include/opencv4/ \
                /home/zhengbo/Desktop/opencv/install/include/opencv4/opencv2/core

LIBS += /home/zhengbo/Desktop/opencv/install/lib/libopencv_highgui.so \
        /home/zhengbo/Desktop/opencv/install/lib/libopencv_core.so    \
        /home/zhengbo/Desktop/opencv/install/lib/libopencv_imgproc.so \
        /home/zhengbo/Desktop/opencv/install/lib/libopencv_imgcodecs.so\
        /home/zhengbo/Desktop/opencv/install/lib/libopencv_videoio.so
       # LIBS += -L/home/zhengbo/Desktop/opencv/install/lib  # OpenCV库路径
       # LIBS += -lopencv_core -lopencv_highgui -lopencv_videoio  # 必须包含videoio
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abnormal.cpp \
    aboutus.cpp \
    main.cpp \
    mainmonitor.cpp \
    mainwindow.cpp \
    my_sql.cpp \
    ph_page.cpp \
    serialdate.cpp \
    serialport.cpp \
    set_help.cpp \
    tcpnet.cpp \
    temperture_page.cpp \
    waterlevel_page.cpp \
    welcome.cpp \
    wet_page.cpp \
    widget.cpp

HEADERS += \
    abnormal.h \
    aboutus.h \
    mainmonitor.h \
    mainwindow.h \
    my_sql.h \
    ph_page.h \
    serialdate.h \
    serialport.h \
    set_help.h \
    tcpnet.h \
    temperture_page.h \
    waterlevel_page.h \
    welcome.h \
    wet_page.h \
    widget.h

FORMS += \
    abnormal.ui \
    aboutus.ui \
    mainmonitor.ui \
    mainwindow.ui \
    ph_page.ui \
    serialdate.ui \
    serialport.ui \
    set_help.ui \
    temperture_page.ui \
    waterlevel_page.ui \
    welcome.ui \
    wet_page.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Image/picture.qrc

DISTFILES += \
    Image/background.jpg \
    Image/jxust.jpg
