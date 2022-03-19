QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client/board.cpp \
    client/board_controller.cpp \
    client/board_view.cpp \
    client/client.cpp \
    client/friendslist_menu.cpp \
    client/game.cpp \
    client/game_menu.cpp \
    client/main_menu.cpp \
    client/menu.cpp \
    client/menu_connection.cpp \
    client/move_management.cpp \
    client/player.cpp \
    common/common.cpp \
    common/socketlib.cpp \
    generalwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    menuwindow.cpp \
    server/client_user.cpp \
    server/matchmaking.cpp \
    server/server.cpp

HEADERS += \
    client/board.hpp \
    client/board_controller.hpp \
    client/board_view.hpp \
    client/client.hpp \
    client/friendslist_menu.hpp \
    client/game.hpp \
    client/game_menu.hpp \
    client/main_menu.hpp \
    client/menu.hpp \
    client/menu_connection.hpp \
    client/move_management.hpp \
    client/player.hpp \
    common/common.hpp \
    common/socketlib.hpp \
    abstractwindow.h \
    constante.h \
    generalwindow.h \
    mainwindow.h \
    menuwindow.hpp \
    observer.hpp \
    server/client_user.hpp \
    server/matchmaking.hpp \
    server/server.hpp

FORMS += \
    mainwindow.ui \
    menuwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES += \
    test.txt
