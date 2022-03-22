#ifndef GENERALWINDOW_H
#define GENERALWINDOW_H

#include "mainwindow.h"
#include "menuwindow.hpp"
#include "gamewindow.h"

#include "observer.hpp"
#include "abstractwindow.h"
#include "constante.h"
#include <client/client.hpp>
#include <client/menu_connection.hpp>
#include <QObject>
#include <QWidget>
#include <QWindow>
#include <QVector>
#include <QSharedPointer>
#include <QEnableSharedFromThis>
#include <memory>

class generalWindow: public Observer, public QEnableSharedFromThis<generalWindow>
{
private:
    int actual_window = 0;
    QVector<QSharedPointer<AbstractWindow>> windows;


public:
    generalWindow(QSharedPointer<MainWindow> w, QSharedPointer<menuWindow> m, QSharedPointer<gameWindow> ga);
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
