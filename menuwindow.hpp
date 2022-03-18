#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QDialog>
#include <string.h>
#include <ctime>
#include <client/client.hpp>
#include <client/menu_connection.hpp>
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
    Client c;

public:
    explicit menuWindow(QWidget *parent = nullptr);
    ~menuWindow();
    void show_screen(int to_load);
    void change_screen(int screen);
    bool check_pseudo(std::string pseudo);
    void update_ranking(RankingData data);



private:
    Ui::menuWindow *ui;
    int actual_page = MAIN_MENU;

private slots:
    void play_game();
    void matchmaking();
    void retour();
    void friend_management();
    void friend_man_add();
    void friend_man_pseudo();
    void ranking();
    void deco();
    void update_ranking_slot();
};

#endif // MENUWINDOW_H
