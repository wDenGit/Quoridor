#include "game.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game w;
    w.make_buttons();
    w.updateButtons();
    w.show();
    return a.exec();
}
