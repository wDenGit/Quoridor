#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
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
};

#endif // MAINWINDOW_H
