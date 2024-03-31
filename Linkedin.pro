QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

RC_ICONS = Resources/linkedin.ico

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    Sources/splash.cpp \
    Sources/login.cpp \
    Sources/verification.cpp \
    Sources/profile.cpp

HEADERS += \
    Headers/splash.h \
    Headers/login.h \
    Headers/verification.h \
    Headers/profile.h

FORMS += \
    Forms/splash.ui \
    Forms/login.ui \
    Forms/verification.ui \
    Forms/profile.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources/assets.qrc
