//#include "mainwindow.h"
//#include "menuwindow.h"
#include "generalwindow.h"
#include <memory>

#include <QApplication>
#include <QSharedPointer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSharedPointer<generalWindow> g = QSharedPointer<generalWindow>(new generalWindow);
    g->create_windows();

    // generalWindow window;
    g->run_game();
    return a.exec();
}
