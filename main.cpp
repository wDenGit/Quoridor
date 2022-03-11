#include "mainwindow.h"
#include "menuwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    menuWindow m;
    // w.show();
    m.show();
    return a.exec();
}
