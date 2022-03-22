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
    QSharedPointer<gameWindow> ga = QSharedPointer<gameWindow>(new gameWindow)  ;
    ga->make_buttons();
    ga->updateButtons();
    QSharedPointer<generalWindow> ge = QSharedPointer<generalWindow>(new generalWindow(w, m, ga));
    ge->create_windows();

    // generalWindow window;
    ge->run_game();
    return a.exec();
}
