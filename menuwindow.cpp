#include "menuwindow.hpp"
#include "connexionwindow.h"
#include "ui_menuwindow.h"

#include <QFileInfo>
#include <QTextStream>
#include <QVector>

#include <iostream>
#include <string>
#include <vector>
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
    connect(ui->pushButton_diconnect, SIGNAL(released()), this, SLOT(deco()));
    connect(ui->pushButton_friend_retour, SIGNAL(released()), this, SLOT(retour()));
    connect(ui->pushButton_add, SIGNAL(released()), this, SLOT(friend_man_add()));
    connect(ui->pushButton_friend_add, SIGNAL(released()), this, SLOT(friend_man_pseudo()));
    connect(ui->pushButton_friend_add_retour, SIGNAL(released()), this, SLOT(retour()));
    connect(ui->pushButton_ranking, SIGNAL(released()), this, SLOT(ranking()));
    connect(ui->pushButton_rank_retour, SIGNAL(released()), this, SLOT(retour()));
    connect(ui->pushButton_rank_add, SIGNAL(released()), this, SLOT(update_ranking_slot()));
    connect(ui->pushButton_fr_liste, SIGNAL(released()), this, SLOT(friend_list()));

}

menuWindow::~menuWindow()
{
    delete ui;
}

bool menuWindow::check_pseudo(string pseudo){
    QString pseudo_read;
    // ifstream read_file ("spo.txt"); // TODO KILL ME PLIZ
    QFile file{QString("/home/bappi/Documents/F209/WORK/PART_3/WORK_3/Quoridor/test.txt")};
    // file.open(QIODevice::ReadOnly);
    if(!file.open(QIODevice::ReadOnly))
        {
            qDebug("Don't exist");
            return false;
        }
    qDebug("Opened");
    QTextStream in(&file);
    while(! in.atEnd()){
        QString tmp = in.readLine();
        cout << "entered" << endl;
        cout << tmp.toUtf8().constData() << endl;
        if (pseudo == tmp.toUtf8().constData()){
            cout << "True" << endl;
            file.close();
            return true;

        }
    }
//   for (QString line = in.readLine();
//         !line.isNull();
//         line = in.readLine()) {
//       cout << "entered" << endl;
//        /* process information */
//    };
    file.close();
    qDebug("finished");
    return false;
}

void menuWindow::show_screen(int to_load){
    actual_page = to_load;
    ui->menuWidget->setCurrentIndex(actual_page);
}

void menuWindow::update_ranking(RankingData data){ // TODO NE PAS PRENDRE EN COMPTE CAR NOUS ALLONS RECEVOIR DES MESSAGES DU SERVEUR
    cout <<"into ranking" << endl;
    char* tmp_char;
    char* num_char;
    sprintf(num_char, "%d", data.score);
    tmp_char = &data.player[0];
    ui->tableRank->setItem(1, 0, new QTableWidgetItem(QString(tmp_char)));
    ui->tableRank->setItem(1, 1, new QTableWidgetItem(QString(num_char)));
//    tm *tmp; // TODO SYSTEM DE DATE NE FONCTIONNE PAS!!!!!!!!!!!!!!!!!!!!!
//    time(&data.date);
//    tmp = localtime(&data.date);
//    char date[100];
    // strftime(date, 100, "%j/%m/%y", tmp);
    //ui->tableRank->setItem(1, 2, new QTableWidgetItem(QString(date)));
}

//void menuWindow::update_ranking(RankingData data){
//    // ifstream read_file ("spo.txt"); // TODO KILL ME PLIZ
//    QFile file{QString("/home/bappi/Documents/F209/WORK/PART_3/WORK_3/Quoridor/test_csv.csv")}; // TODO!!!!!!!!!!!!!!!!
//    // file.open(QIODevice::ReadOnly);
//    if(!file.open(QIODevice::ReadOnly))
//        {
//            qDebug("Don't exist");
//            return false;
//        }
//    qDebug("Opened");
//    QVector<QString> string_vector;
//    QTextStream in(&file);
//    while(! in.atEnd()){
//        QString tmp = in.readLine();
//        string_vector.append(tmp);
//    }

//}

// Slots----------------------------------------------------------------------------------

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

void menuWindow::ranking(){
    show_screen(RANKING);
}

void menuWindow::update_ranking_slot(){
    // update_ranking({"test", 0, time_t});
    update_ranking({string("james"), 0});
}

void menuWindow::deco(){
    exit(0);
}

void menuWindow::friend_list(){
    show_screen(FRIENDS_LIST);
}


