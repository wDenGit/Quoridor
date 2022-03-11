#include "menuwindow.h"
#include "connexionwindow.h"
#include "ui_menuwindow.h"

menuWindow::menuWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menuWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_play, SIGNAL(released()), this, SLOT(play_game()));

}

menuWindow::~menuWindow()
{
    delete ui;
}

void menuWindow::play_game(){
    qDebug("Play Game");

}
