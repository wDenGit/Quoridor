#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>
#include <QDebug>
#include <QGridLayout>
#include <QPushButton>
#include <QSignalMapper>
#include <QDialog>
#include <QString>
#include "./client/board.hpp"
#include "./client/board_controller.hpp"
#include "./client/board_view.hpp"
#include "./client/player.hpp"
#include "./client/client.hpp"
#include "abstractwindow.h"
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class gameWindow;}
QT_END_NAMESPACE

class gameWindow : public QDialog, public AbstractWindow
{
    Q_OBJECT

    QVector<QVector<QPushButton*>> buttons;
    QSignalMapper* mapper;
    const QString letters = "abcdefghijklmnopq";
    std::shared_ptr<Board> board;
    BoardController boardController;
    std::shared_ptr<Player> player;
    std::string stringMove;
    int sizeMove=0;
    BoardView bv;
    std::shared_ptr<Client> c; //inutilisé pour linstant


public:
    explicit gameWindow(std::shared_ptr<Client> c, QWidget *parent = nullptr);
    void delete_buttons();
    void make_buttons();
    void updateButtons() const ;
    bool isCasePawn(std::string move);
    gameWindow* getSelf() override{
        return this;
    }
    ~gameWindow();

private:
    Ui::gameWindow *ui;


private slots:
    void play_game(QString move);
};

#endif // GAMEWINDOW_H
