#include "menuwindow.hpp"
#include "connexionwindow.h"
#include "ui_menuwindow.h"

#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>

using namespace std;

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
    connect(ui->pushButton_add, SIGNAL(released()), this, SLOT(friend_man_add()));
    connect(ui->pushButton_friend_add, SIGNAL(released()), this, SLOT(friend_man_pseudo()));

}

menuWindow::~menuWindow()
{
    delete ui;
}

bool menuWindow::check_pseudo(string pseudo){
    QString pseudo_read;
    ifstream read_file;
    read_file.open("test_2.txt");
    if (read_file.is_open()){
        cout << "okaed" << endl;
    }
    else{
        cout << "Niet okayed" << endl;
    }
    string tmp;
    // cout << "test" << endl;
//    while(getline(read_file, tmp)){
//        cout << "test" << endl;
//        if (pseudo == tmp){
//            return true;
//            qDebug("okay");
//        }
//    }
    qDebug("Not Okay");
    return false;
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

void menuWindow::friend_man_add(){
    qDebug("Add friend");
    show_screen(FRIENDS_ADD);
    // QString recieved = ui->friend_to_add.text();
}

void menuWindow::friend_man_pseudo(){
    qDebug("Add pseudo");
    QString testString = ui->friend_to_add->text();
    qDebug(qUtf8Printable(testString));
    check_pseudo(testString.toUtf8().constData());

}





