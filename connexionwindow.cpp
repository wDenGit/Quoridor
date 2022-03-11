#include "connexionwindow.h"
#include "mainwindow.h"
#include "menuwindow.h"
#include "ui_connexionwindow.h"

connexionWindow::connexionWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::connexionWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_Retour, SIGNAL(released()), this, SLOT(retour_pressed()));
}

connexionWindow::~connexionWindow()
{
    delete ui;
}

void connexionWindow::retour_pressed(){
    qDebug("Retour");
}
