#ifndef FRIENDSLIST_MENU_HPP
#define FRIENDSLIST_MENU_HPP

#include "menu.hpp"
#include <vector>
#include <string>


class FriendsListMenu: public Menu {
    int sock;
    std::vector<int> friendsKey;
    std::vector<std::string> friendsPseudo;
    enum options{addFriendChoice=1, exit=2, max_input=2};
    public:
        FriendsListMenu(int sock): sock{sock} {this->updateAll();};

        void updateAll();
        void run();

    private:
        void updatePseudo();
        void displayFriends();
        void displayOptions();
        bool addFriend(std::string pseudo);
};

#endif