TEMPLATE = lib
TARGET = lipstickplugin
VERSION = 0.1

CONFIG += qt plugin link_pkgconfig c++17
QT += core gui qml quick waylandcompositor dbus
PKGCONFIG += mlite$${QT_MAJOR_VERSION} dsme_dbus_if thermalmanager_dbus_if usb-moded-qt$${QT_MAJOR_VERSION} glib-2.0

equals(QT_MAJOR_VERSION, 6) {
    PKGCONFIG += systemsettings-qt6
} else {
    PKGCONFIG += systemsettings
}

INSTALLS = target qmldirfile
qmldirfile.files = qmldir
qmldirfile.path = $$[QT_INSTALL_QML]/org/nemomobile/lipstick
target.path = $$[QT_INSTALL_QML]/org/nemomobile/lipstick

#FOR BLUEZQT Wait https://invent.kde.org/frameworks/bluez-qt/-/merge_requests/14
INCLUDEPATH += /usr/include/KF$${QT_MAJOR_VERSION}/BluezQt
LIBS += -lKF$${QT_MAJOR_VERSION}BluezQt

DEPENDPATH += ../src
INCLUDEPATH += ../src \
    ../src/utilities \
    ../src/xtools \
    ../src/compositor \
    ../src/devicestate \
    ../src/touchscreen

LIBS += -L../src -llipstick-qt$${QT_MAJOR_VERSION}

HEADERS += \
    lipstickplugin.h

SOURCES += \
    lipstickplugin.cpp

OTHER_FILES += \
    qmldir

QMAKE_CXXFLAGS += \
    -Werror \
    -g \
    -fPIC \
    -fvisibility=hidden \
    -fvisibility-inlines-hidden

QMAKE_LFLAGS += \
    -pie \
    -rdynamic
