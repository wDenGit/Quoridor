#ifndef BOARD_HPP
#define BOARD_HPP

#include <QDebug>
#include <vector>
#include <memory>
#include <array>
#include <string>
#include <iostream>     // DEBUG

struct Point{
    int x,y;
};

class Entity {
    public:
        Entity()=default;
        virtual int getPlayer()=0;
};
class Wall: public Entity {
    int player;
    public:
        Wall()=default;
        int getPlayer(){return player;}
};

class Pawn: public Entity {
    int player;
    Point pos;
    public:
        Pawn(int player): player{player} {};
        int getPlayer() {return player;}
        void setPos(Point newPos) {this->pos = newPos;}
        Point getPos() {return this->pos;};

};

class Case {
    std::shared_ptr<Entity> entity =nullptr;
    Point pos;
    std::vector<std::shared_ptr<Case>> pawnCaseNeighbor;
    std::vector<std::shared_ptr<Case>> wallCaseNeighbor;
    int caseType;
    public:
        enum caseT{wall, pawn};
        Case(int type, int x, int y);

        // Setter & Getter
        void setPawnNeighbors(std::vector<std::shared_ptr<Case>> v) {pawnCaseNeighbor = v;}
        void setWallNeighbors(std::vector<std::shared_ptr<Case>> v) {wallCaseNeighbor = v;}
        std::vector<std::shared_ptr<Case>> getPawnCaseNeighbors() {return pawnCaseNeighbor;}
        std::vector<std::shared_ptr<Case>> getWallCaseNeighbors() {return wallCaseNeighbor;}

        bool isEmpty() const {return entity == nullptr;}
        bool isPawnCase() const {return caseType == pawn;}
        void put(std::shared_ptr<Entity> newEntity);

        int getPlayer_1(); // Recuperer le joueur

        Point getPos() const {return pos;}

        void setEmpty() {entity = nullptr;}
};


class Board {
    std::vector<std::vector<std::shared_ptr<Case>>> board;
    int size;
    std::array<Point,4> pawns={{-1,-1}};

    void initializeNeighbors();
    public:
        Board(int caseNumber=9);

        const std::vector<std::vector<std::shared_ptr<Case>>> &getBoard() const {return board;}

        size_t getSize() const {return board.size();}

        bool checkEmptyCase(Point pos) const;

        bool checkCaseType(Point pos) const;

        int checkWinner();

        bool checkPath(std::vector<Point> point, Board board);

        void putWall(std::shared_ptr<Wall> newWall, Point pos1, Point pos2, Point pos3);

        void putPawn(std::shared_ptr<Pawn> newPawn, Point pos);

        void removePawn(Point p_pawn);

        void removeWall(Point pos1, Point pos2, Point pos3);
        std::array<Point,4> getPawn() {return pawns;}

        std::shared_ptr<Case> getCase(Point pos);



};

#endif
