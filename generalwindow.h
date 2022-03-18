#ifndef GENERALWINDOW_H
#define GENERALWINDOW_H

#include "mainwindow.h"
#include "menuwindow.hpp"
#include "observer.hpp"
#include "abstractwindow.h"
#include "constante.h"

#include <QObject>
#include <QWidget>
#include <QWindow>
#include <QVector>
#include <QSharedPointer>
#include <QEnableSharedFromThis>

class generalWindow: public Observer, public QEnableSharedFromThis<generalWindow>
{
private:
    QSharedPointer<MainWindow> w = QSharedPointer<MainWindow>(new MainWindow);
    QSharedPointer<menuWindow> m = QSharedPointer<menuWindow>(new menuWindow);
    int actual_window = 0;
    QVector <QSharedPointer<AbstractWindow>> windows;

public:
    generalWindow();
    ~generalWindow();
    void run_game();
    void switch_window(int windowToShow);
    void create_windows();
    void update(int windowToShow) override;
    QSharedPointer<generalWindow> getSelf_qshared_ptr(){
            return sharedFromThis();
    };
};

#endif // GENERALWINDOW_H
