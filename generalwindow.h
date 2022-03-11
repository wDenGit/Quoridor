#ifndef GENERALWINDOW_H
#define GENERALWINDOW_H

#include "mainwindow.h"
#include "menuwindow.h"

#include <QObject>
#include <QWidget>

class generalWindow
{
private:
    MainWindow w;
    menuWindow m;
    int actual_window = 0;

public:
    generalWindow() {};
    void run_game();
};

#endif // GENERALWINDOW_H
