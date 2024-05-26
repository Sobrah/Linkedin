QT += core gui widgets sql network concurrent

CONFIG += c++17

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=6

SOURCES += \
    main.cpp \
    Sources/window.cpp \
    Sources/splash.cpp \
    Sources/login.cpp \
    Sources/verification.cpp \
    Sources/profile.cpp \
    Sources/home.cpp \
    Sources/content.cpp \
    Sources/post.cpp \
    Sources/account.cpp

HEADERS += \
    Headers/window.h \
    Headers/splash.h \
    Headers/login.h \
    Headers/verification.h \
    Headers/profile.h \
    Headers/home.h \
    Headers/content.h \
    Headers/post.h \
    Headers/account.h

FORMS += \
    Forms/splash.ui \
    Forms/login.ui \
    Forms/verification.ui \
    Forms/profile.ui \
    Forms/window.ui \
    Forms/home.ui

RESOURCES += \
    Resources/assets.qrc

RC_ICONS = Resources/linkedin.ico
