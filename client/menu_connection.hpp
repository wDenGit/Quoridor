#ifndef MENU_CONNECTION_HPP
#define MENU_CONNECTION_HPP

#include <string>
#include "menu.hpp"

class MenuConnection: public Menu {
    public:
        static int createAccount(int client_socket, std::string pseudo, std::string mdp);// return 0 si creation reussi, snn -1
        static int connection(int client_socket, std::string pseudo, std::string mdp);   // return -1 si connection rate, snn renvoie la clé lié a notre compte
};

#endif
