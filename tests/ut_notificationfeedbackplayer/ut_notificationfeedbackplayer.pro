include(../common.pri)
TARGET = ut_notificationfeedbackplayer
INCLUDEPATH += $$NOTIFICATIONSRCDIR /usr/include/ngf-qt5
CONFIG += link_pkgconfig
QT += dbus

HEADERS += \
    ut_notificationfeedbackplayer.h \
    $$NOTIFICATIONSRCDIR/notificationfeedbackplayer.h \
    $$NOTIFICATIONSRCDIR/notificationmanager.h \
    $$NOTIFICATIONSRCDIR/notification.h \
    /usr/include/ngf-qt5/ngfclient.h

SOURCES += \
    ut_notificationfeedbackplayer.cpp \
    $$NOTIFICATIONSRCDIR/notificationfeedbackplayer.cpp \
    $$NOTIFICATIONSRCDIR/notification.cpp \
    $$STUBSDIR/stubbase.cpp

