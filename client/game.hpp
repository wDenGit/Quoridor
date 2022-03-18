#ifndef GAME_HPP
#define GAME_HPP

#include "board_view.hpp"
#include "board.hpp"
#include "board_controller.hpp"
#include "player.hpp"

#include <vector>
#include <string>



class Game {
    const int nb_players;
    int accKey;
    std::shared_ptr<Board> board;
    BoardController boardController;
    BoardView boardView;
    std::vector<std::shared_ptr<Player>> players;
    const int sock;
    int myOrder;

    public: 
        Game(int sock, int myKey, std::vector<int> keys);
        void playGame();

        void cancelGame();
        // ask and check the move, if the move is valid ->return string / "exit" si l'on veut quitter
        std::string askAndCheckUserInput();
        /* wait for packet from server 
        return true si coup jouer | return false -> si la partie a été annulé */
        bool waitOtherPlayerInput(std::shared_ptr<Player> otherPlayer);
        void tellServerGameFinish(int winner);

        // void setPlayers() {};

    private:
        void initPlayers(std::vector<int> keys);
        void initPawn();
        void clearTerminal();
        std::string askMove();

};

#endif