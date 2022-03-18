#ifndef GAME_MENU_HPP
#define GAME_MENU_HPP

#include "menu.hpp"
#include <string>

class GameMenu: public Menu {
    const int sock;
    const int myKey;

    enum options{randomMatchmaking2players=1, randomMatchmaking4players=2, exit=3, max_input=3};    //TODO more options
    public:
        GameMenu(int sock, int myKey): sock{sock}, myKey{myKey} {};
        
        void run();
    private:
        void displayPlayGameMenu();
        void startGame(std::string serverRequest);
};


#endif