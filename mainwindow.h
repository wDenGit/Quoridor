#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <client/client.hpp>
#include <client/menu_connection.hpp>
#include <memory>
#include <string>
#include "abstractwindow.h"
#include "observer.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public AbstractWindow
{
    Q_OBJECT
    std::shared_ptr<Client> c; // PROBS METTRE LE CLIENT A L'EXTERIEUR POUR QUE TOUT LE MONDE AIT ACCES

public:
    MainWindow(std::shared_ptr<Client> c, QWidget *parent = nullptr);
    ~MainWindow();
    int setup_client(QString ip);
    // int get_ip();
    MainWindow* getSelf() override{
        return this;
    }

private:
    Ui::MainWindow *ui;
    // int ip;

private slots:
    void connexion_pressed();
    void inscription_pressed();
    void quitter_pressed();
    void retour_pressed();
    void envoyer_pressed_2();
    void envoyer_pressed_3();
    void envoyer_pressed_4();
};

#endif // MAINWINDOW_H
