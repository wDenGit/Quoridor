#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QSharedPointer>
#include <QDebug>
#include <QGridLayout>
#include <QPushButton>
#include <QSignalMapper>
#include <QDialog>
#include "board.hpp"
#include "board_controller.hpp"
#include "player.hpp"
#include <QLabel>
#include <QRectF>
namespace Ui {
class game;
}

class game : public QDialog
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


public:
    explicit game(QWidget *parent = nullptr);
    void delete_buttons();
    void make_buttons();
    void updateButtons() const ;
    bool isCasePawn(std::string move);
    ~game();

private:
    Ui::game *ui;


private slots:
    void play_game(QString move);
};

#endif // GAME_H
