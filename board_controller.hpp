#ifndef BOARD_CONTROLLER_HPP
#define BOARD_CONTROLLER_HPP

#include "move_management.hpp"
#include "board.hpp"
#include "player.hpp"

#include <vector>
#include <iostream> //DEBUG


class BoardController { 
    std::shared_ptr<Board> board;
    ControlMove controlMove;
    public:
        BoardController(std::shared_ptr<Board> board): board{board}, controlMove{board} {}

        // bool waitMove(int player);
        bool checkMove(std::shared_ptr<Player> player, std::string move);
        void makeMove(std::shared_ptr<Player> player, std::string move);
        
        bool checkWall(std::vector<Point> wallPoint);

        Point stringToPoint(std::string pos);

        std::vector<Point> moveParser(std::string s);

        bool checkWallSyntax(std::vector<Point> wallPoint);

        Point fillWallPoint(std::vector<Point> wallPoint);

        std::vector<std::string> removeSpace(std::string str);

        bool checkValideLetter(std::string letter);

        bool checkValideNumber(std::string number);

        bool checkWallGoodPos(std::vector<Point> wallPoint);

        bool is_in(Point casePos, std::vector<Point> *posAlreadyVisited);

        bool searchPath(std::shared_ptr<Case> casemain, Point dest, std::vector<Point> *PosAlreadyVisited);

        bool checkPath(Point pos1, Point pos2, Point pos3, std::shared_ptr<Wall> wall);
};

#endif
