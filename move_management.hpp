#ifndef MOVE_MANAGEMENT_HPP
#define MOVE_MANAGEMENT_HPP

#include "board.hpp"


class ControlMove {
    std::shared_ptr<Board> board;
    public:
        ControlMove(std::shared_ptr<Board> board) : board{board} {};

        bool checkAlignment(std::shared_ptr<Case> case_main, std::shared_ptr<Case> neighborsPawnCase, std::shared_ptr<Case> neighborsWallCase);

        bool isAligner(std::shared_ptr<Case> case1, std::shared_ptr<Case> case2, std::shared_ptr<Case> wall);

        bool isWallBetween(std::shared_ptr<Case> pawnCase1, std::shared_ptr<Case> pawnCase2, std::shared_ptr<Case> wallCase);
        
        void printPos(std::vector<std::shared_ptr<Case>> vec);

        std::vector<std::shared_ptr<Case>> checkMovement(std::shared_ptr<Case> case_main);
                
        void highlightPlayable(){}

        
        // void printNeighbors(Point pos);

        std::vector<Point> sendMovePossible(Point p);
        
        // bool movePawn(Point pos_init, Point pos_dest);
};

#endif
