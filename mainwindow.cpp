#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(3);

    connect(ui->pushButton_Connexion, SIGNAL(released()), this, SLOT(connexion_pressed()));
    connect(ui->pushButton_Inscription, SIGNAL(released()), this, SLOT(inscription_pressed()));
    connect(ui->pushButton_Quitter, SIGNAL(released()), this, SLOT(quitter_pressed()));

    connect(ui->pushButton_Retour_2, SIGNAL(released()), this, SLOT(retour_pressed()));
    connect(ui->pushButton_Retour_3, SIGNAL(released()), this, SLOT(retour_pressed()));
    connect(ui->pushButton_Envoyer_2, SIGNAL(released()), this, SLOT(envoyer_pressed_2()));
    connect(ui->pushButton_Envoyer_3, SIGNAL(released()), this, SLOT(envoyer_pressed_3()));
    connect(ui->pushButton_Envoyer_4, SIGNAL(released()), this, SLOT(envoyer_pressed_4()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::setup_client(QString ip){
    return c.run(8080, ip.toStdString());
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
    qDebug("Envoyer2");
    QString pseudo = ui->lineEdit_Login_2->text();
    QString mdp = ui->lineEdit_Mdp_2->text();
}
void MainWindow::envoyer_pressed_3(){
    qDebug("Envoyer3");
    QString pseudo = ui->lineEdit_Login_3->text();
    QString mdp = ui->lineEdit_Mdp_3->text();
    QString confMdp = ui->lineEdit_ConfirmationMdp_3->text();
}

void MainWindow::envoyer_pressed_4(){
    qDebug("Envoyer4");
    QString IP = ui->lineEdit_IP_4->text();
    if(this->setup_client(IP) == 0){
        ui->stackedWidget->setCurrentIndex(0);
    }
}
