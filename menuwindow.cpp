#include "menuwindow.h"
#include "connexionwindow.h"
#include "ui_menuwindow.h"

menuWindow::menuWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menuWindow)
{
    ui->setupUi(this);

    ui->menuWidget->setCurrentIndex(actual_page);
    connect(ui->pushButton_play, SIGNAL(released()), this, SLOT(play_game()));
    connect(ui->pushButton_retour, SIGNAL(released()), this, SLOT(retour()));
    connect(ui->pushButton_friends, SIGNAL(released()), this, SLOT(friend_management()));
    connect(ui->pushButton_friend_retour, SIGNAL(released()), this, SLOT(retour()));

}

menuWindow::~menuWindow()
{
    delete ui;
}

void menuWindow::show_screen(int to_load){
    actual_page = to_load;
    ui->menuWidget->setCurrentIndex(actual_page);
}

void menuWindow::play_game(){
    qDebug("Play Game");
    show_screen(PLAY);
}

void menuWindow::retour(){
    qDebug("Retour");
    // actual_page--;
    show_screen(MAIN_MENU);
}

void menuWindow::friend_management(){
    qDebug("Friends");
    show_screen(FRIENDS);
}
