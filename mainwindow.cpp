#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_Connexion, SIGNAL(released()), this, SLOT(connexion_pressed()));
    connect(ui->pushButton_Inscription, SIGNAL(released()), this, SLOT(inscription_pressed()));
    connect(ui->pushButton_Quitter, SIGNAL(released()), this, SLOT(quitter_pressed()));

    connect(ui->pushButton_Retour_2, SIGNAL(released()), this, SLOT(retour_pressed()));
    connect(ui->pushButton_Retour_3, SIGNAL(released()), this, SLOT(retour_pressed()));
    connect(ui->pushButton_Envoyer_2, SIGNAL(released()), this, SLOT(envoyer_pressed_2()));
    connect(ui->pushButton_Envoyer_3, SIGNAL(released()), this, SLOT(envoyer_pressed_3()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connexion_pressed(){
    qDebug("Connexion");
    /*hide();
    connexionWindow_ = new connexionWindow(this);
    connexionWindow_->show();
    */
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::inscription_pressed(){
    qDebug("Inscription");
    ui->stackedWidget->setCurrentIndex(2);
}
void MainWindow::quitter_pressed(){
    qDebug("Quitter");
}

void MainWindow::retour_pressed(){
    qDebug("Retour");
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::envoyer_pressed_2(){
    qDebug("Envoyer");
    //QString pseudo = ui->lineEdit_Login_2;
    QString mdp;
}
void MainWindow::envoyer_pressed_3(){
    qDebug("Envoyer");
    //QString pseudo = ui->lineEdit_Login_3;
    QString mdp;
}
