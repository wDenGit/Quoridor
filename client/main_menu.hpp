#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "menu.hpp"
#include <string>

class MainMenu: public Menu {
    enum options{playGame=1, resumeGame=2, seeFriends=3, seeRanking=4, disconnect=5, max_input=5};
    const int account;
    const int sock;

    public:
        MainMenu(int userId, int sock): account{userId}, sock{sock} {};
        void run();
    private:
        void displayMenu();
};

#endif