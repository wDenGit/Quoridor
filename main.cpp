//#include "mainwindow.h"
//#include "menuwindow.h"
#include "generalwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    menuWindow m;
//    // w.show();
//    m.show();
    generalWindow window;
    window.run_game();
    return a.exec();
}
