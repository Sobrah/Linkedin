QT += core gui widgets sql network concurrent

CONFIG += c++17

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=6

SOURCES += \
    Sources/account.cpp \
    Sources/comment.cpp \
    Sources/content.cpp \
    Sources/directmessage.cpp \
    Sources/like.cpp \
    Sources/post.cpp \
    main.cpp \
    Sources/splash.cpp \
    Sources/login.cpp \
    Sources/verification.cpp \
    Sources/profile.cpp \
    Sources/window.cpp

HEADERS += \
    Headers/account.h \
    Headers/comment.h \
    Headers/content.h \
    Headers/directmessage.h \
    Headers/like.h \
    Headers/post.h \
    Headers/splash.h \
    Headers/login.h \
    Headers/verification.h \
    Headers/profile.h \
    Headers/window.h

FORMS += \
    Forms/splash.ui \
    Forms/login.ui \
    Forms/verification.ui \
    Forms/profile.ui \
    Forms/window.ui

RESOURCES += \
    Resources/assets.qrc

RC_ICONS = Resources/linkedin.ico
