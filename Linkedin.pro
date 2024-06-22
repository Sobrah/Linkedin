QT += core gui widgets sql network concurrent

CONFIG += c++17

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=6

SOURCES += \
    main.cpp \
    # Page Sources
    Sources/window.cpp \
    Sources/splash.cpp \
    Sources/login.cpp \
    Sources/verification.cpp \
    Sources/profile.cpp \
    Sources/home.cpp \
    Sources/collection.cpp \
    Sources/viewpost.cpp \
    Sources/networkcompany.cpp \
    Sources/jobcompany.cpp \
    Sources/jobperson.cpp \
    Sources/jobposition.cpp \
    Sources/jobcandidate.cpp \
    Sources/me.cpp \
    Sources/viewprofile.cpp \
    # Logic Sources
    Sources/utility.cpp \
    Sources/account.cpp \
    Sources/company.cpp \
    Sources/like.cpp \
    Sources/person.cpp \
    Sources/content.cpp \
    Sources/post.cpp \
    Sources/job.cpp \

HEADERS += \
    Header \
    # Page Headers
    Headers/window.h \
    Headers/splash.h \
    Headers/login.h \
    Headers/verification.h \
    Headers/profile.h \
    Headers/home.h \
    Headers/collection.h \
    Headers/viewpost.h \
    Headers/networkcompany.h \
    Headers/jobcompany.h \
    Headers/jobperson.h \
    Headers/jobposition.h \
    Headers/jobcandidate.h \
    Headers/me.h \
    Headers/viewprofile.h \
    # Logic Headers
    Headers/utility.h \
    Headers/account.h \
    Headers/company.h \
    Headers/like.h \
    Headers/person.h \
    Headers/content.h \
    Headers/post.h \
    Headers/job.h \

FORMS += \
    Forms/window.ui \
    Forms/splash.ui \
    Forms/login.ui \
    Forms/verification.ui \
    Forms/profile.ui \
    Forms/home.ui \
    Forms/collection.ui \
    Forms/viewpost.ui \
    Forms/networkcompany.ui \
    Forms/viewprofile.ui \
    Forms/jobcompany.ui \
    Forms/jobperson.ui \
    Forms/jobposition.ui \
    Forms/jobcandidate.ui \
    Forms/me.ui \

RESOURCES += \
    Resources/assets.qrc

RC_ICONS = Resources/linkedin.ico
