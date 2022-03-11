#include "menuwindow.h"
#include "connexionwindow.h"
#include "ui_menuwindow.h"

menuWindow::menuWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menuWindow)
{
    ui->setupUi(this);
}

menuWindow::~menuWindow()
{
    delete ui;
}
