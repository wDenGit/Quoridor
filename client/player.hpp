#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "board.hpp"

#include <memory>
#include <iostream> //DEBUG

class Player{
    int acc_key;
    int playerOrder;
    const std::string pseudo;
    int wallAvailable;
    std::shared_ptr<Pawn> pawn;
    
    public:
        Player(int key, int order, std::string pseudo, int wallAvailable): acc_key{key}, playerOrder{order}, pseudo{pseudo}, wallAvailable{wallAvailable} {}

        // SETTER
        void setPawn(std::shared_ptr<Pawn> p);

        // GETTER
        int getPlayerOrder();
        std::shared_ptr<Pawn> getPawn();
        std::shared_ptr<Wall> getWall();
        std::string getPseudo() {return this->pseudo;}

        // OTHER Methods
        bool hasWall();
        
};

#endif