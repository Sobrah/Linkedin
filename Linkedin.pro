QT += core gui widgets sql network concurrent

CONFIG += c++17

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=6

SOURCES += \
    Sources/account.cpp \
    Sources/collection.cpp \
    Sources/comment.cpp \
    Sources/company.cpp \
    Sources/content.cpp \
    Sources/directmessage.cpp \
    Sources/home.cpp \
    Sources/job.cpp \
    Sources/jobcandidate.cpp \
    Sources/jobcompany.cpp \
    Sources/jobperson.cpp \
    Sources/jobposition.cpp \
    Sources/like.cpp \
    Sources/login.cpp \
    Sources/main.cpp \
    Sources/me.cpp \
    Sources/networkcompany.cpp \
    Sources/networkfollower.cpp \
    Sources/networkperson.cpp \
    Sources/networkrequest.cpp \
    Sources/networksuggestion.cpp \
    Sources/person.cpp \
    Sources/post.cpp \
    Sources/profile.cpp \
    Sources/splash.cpp \
    Sources/time.cpp \
    Sources/utility.cpp \
    Sources/verification.cpp \
    Sources/viewcomment.cpp \
    Sources/viewlike.cpp \
    Sources/viewpost.cpp \
    Sources/viewprofile.cpp \
    Sources/window.cpp

HEADERS += \
    Headers/account.h \
    Headers/collection.h \
    Headers/comment.h \
    Headers/company.h \
    Headers/content.h \
    Headers/directmessage.h \
    Headers/home.h \
    Headers/job.h \
    Headers/jobcandidate.h \
    Headers/jobcompany.h \
    Headers/jobperson.h \
    Headers/jobposition.h \
    Headers/like.h \
    Headers/login.h \
    Headers/me.h \
    Headers/networkcompany.h \
    Headers/networkfollower.h \
    Headers/networkperson.h \
    Headers/networkrequest.h \
    Headers/networksuggestion.h \
    Headers/person.h \
    Headers/post.h \
    Headers/profile.h \
    Headers/splash.h \
    Headers/time.h \
    Headers/utility.h \
    Headers/verification.h \
    Headers/viewcomment.h \
    Headers/viewlike.h \
    Headers/viewpost.h \
    Headers/viewprofile.h \
    Headers/window.h \
    Logics \
    Views

FORMS += \
    Forms/collection.ui \
    Forms/home.ui \
    Forms/jobcandidate.ui \
    Forms/jobcompany.ui \
    Forms/jobperson.ui \
    Forms/jobposition.ui \
    Forms/login.ui \
    Forms/me.ui \
    Forms/networkcompany.ui \
    Forms/networkfollower.ui \
    Forms/networkperson.ui \
    Forms/networkrequest.ui \
    Forms/networksuggestion.ui \
    Forms/profile.ui \
    Forms/splash.ui \
    Forms/verification.ui \
    Forms/viewcomment.ui \
    Forms/viewlike.ui \
    Forms/viewpost.ui \
    Forms/viewprofile.ui \
    Forms/window.ui \

RESOURCES += \
    Resources/assets.qrc

RC_ICONS = Resources/linkedin.ico
