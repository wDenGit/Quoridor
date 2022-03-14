#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <client/client.hpp>
#include <client/menu_connection.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Client c;

public:
    MainWindow(QWidget *parent = nullptr);
    int setup_client(QString ip);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

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
