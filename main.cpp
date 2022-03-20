//#include "mainwindow.h"
//#include "menuwindow.h"
#include "generalwindow.h"
#include <memory>

#include <QApplication>
#include <QSharedPointer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::shared_ptr<Client> c = std::make_shared<Client>();
    QSharedPointer<MainWindow> w = QSharedPointer<MainWindow>(new MainWindow(c));
    QSharedPointer<menuWindow> m = QSharedPointer<menuWindow>(new menuWindow(c));
    QSharedPointer<generalWindow> g = QSharedPointer<generalWindow>(new generalWindow(w, m));
    g->create_windows();

    // generalWindow window;
    g->run_game();
    return a.exec();
}
