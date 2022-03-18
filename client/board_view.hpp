#ifndef BOARD_VIEW_HPP
#define BOARD_VIEW_HPP

#include "board.hpp"
#include <iostream> //DEBUG

class BoardView {
    private:
        std::shared_ptr<Board> board;
    public:
        BoardView(std::shared_ptr<Board> board): board{board} {}
        void draw() const;
};

#endif