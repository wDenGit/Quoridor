#include "mainwindow.h"
#include "constante.h"
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
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::inscription_pressed(){
    ui->stackedWidget->setCurrentIndex(2);
}
void MainWindow::quitter_pressed(){
    QApplication::quit();
}

void MainWindow::retour_pressed(){
    ui->stackedWidget->setCurrentIndex(0);
}

//Connexion
void MainWindow::envoyer_pressed_2(){
    QString pseudo = ui->lineEdit_Login_2->text();
    QString mdp = ui->lineEdit_Mdp_2->text();
    int userId = MenuConnection::connection(this->c.getClient_socket(), pseudo.toStdString(), mdp.toStdString());
    ui->label_ErrorLogin_2->setText("");
    if(userId > 0) {
        this->notifyObservers(WINDOW_CONNECT+1);
    }
    else{
        //TODO rajouter des messages specifiques: -pseudo incorrect -mdp incorrect -deja connecte
        ui->label_ErrorLogin_2->setText("Pseudo ou mot de passe incorrect.");
    }
}

//Inscription
void MainWindow::envoyer_pressed_3(){
    QString pseudo = ui->lineEdit_Login_3->text();
    QString mdp = ui->lineEdit_Mdp_3->text();
    QString confMdp = ui->lineEdit_ConfirmationMdp_3->text();

    ui->label_ErrorConfirmationMdp_3->setText("");
    ui->label_ErrorLogin_3->setText("");
    if(mdp != confMdp){
        ui->label_ErrorConfirmationMdp_3->setText("Les mots de passe ne sont pas les memes.");//TODO reduire taille msg erreurs et les faire scroller par eux memes
    }else{
        //TODO empecher pseudo vide et mdp vide coté serv
        //TODO Directement connecter joueur
        if(MenuConnection::createAccount(this->c.getClient_socket(), pseudo.toStdString(), mdp.toStdString()) == 0) {
            qDebug("Creation reussite");
        }
        else{
            ui->label_ErrorLogin_3->setText("Ce pseudo est déja utilisé.");
        }
    }
}

//Connexion IP Serveur
void MainWindow::envoyer_pressed_4(){
    QString IP = ui->lineEdit_IP_4->text();
    ui->label_ErrorIP_4->setText("");
    if(this->setup_client(IP) == 0){
        ui->stackedWidget->setCurrentIndex(0);
    }else{
        ui->label_ErrorIP_4->setText("Aucun serveur à cette addresse IP");
    }
}
