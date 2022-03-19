//#include "mainwindow.h"
//#include "menuwindow.h"
#include "generalwindow.h"
#include <memory>

#include <QApplication>
#include <QSharedPointer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSharedPointer<MainWindow> w = QSharedPointer<MainWindow>(new MainWindow);
    QSharedPointer<menuWindow> m = QSharedPointer<menuWindow>(new menuWindow);
    QSharedPointer<generalWindow> g = QSharedPointer<generalWindow>(new generalWindow(w, m));
    g->create_windows();

    // generalWindow window;
    g->run_game();
    return a.exec();
}
