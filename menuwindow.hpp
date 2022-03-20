#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QDialog>
#include <QSound>
#include <string.h>
#include <ctime>
#include <client/client.hpp>
#include <client/menu_connection.hpp>
#include <client/friendslist_menu.hpp>
#include <memory>
#include "constante.h"
#include "mainwindow.h"
#include "observer.hpp"
#include "abstractwindow.h"

struct RankingData{
    std::string player;
    int score;
    std::time_t date;
};

namespace Ui {
class menuWindow;
}

class menuWindow : public QDialog, public AbstractWindow
{
    Q_OBJECT
    std::shared_ptr<Client> c;

public:
    explicit menuWindow(std::shared_ptr<Client> c, QWidget *parent = nullptr);
    ~menuWindow();
    void show_screen(int to_load);
    void change_screen(int screen);
    bool check_pseudo(std::string pseudo);
    void update_ranking(RankingData data);
    void update_friend_list();
    void add_friend();
    menuWindow* getSelf() override{
        return this;
    }



private:
    Ui::menuWindow *ui;
    int actual_page = MAIN_MENU;
    // QSound QSound::audio(QString("audio/USSR.wav"));
//    int sock;
//    FriendsListMenu friendsListMenu;
private slots:
    void play_game();
    void matchmaking();
    void retour();
    void friend_management();
    void friend_man_add();
    void friend_man_pseudo();
    void friend_list();
    void ranking();
    void deco();
    void update_ranking_slot();
};

#endif // MENUWINDOW_H
