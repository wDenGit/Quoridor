#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QDialog>
#include "constante.h"
namespace Ui {
class menuWindow;
}

class menuWindow : public QDialog
{
    Q_OBJECT

public:
    explicit menuWindow(QWidget *parent = nullptr);
    ~menuWindow();
    void show_screen(int to_load);
    void change_screen(int screen);

private:
    Ui::menuWindow *ui;
    int actual_page = MAIN_MENU;

private slots:
    void play_game();
    void retour();
    void friend_management();
};

#endif // MENUWINDOW_H
