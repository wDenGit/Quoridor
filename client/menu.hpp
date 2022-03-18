#ifndef MENU_HPP
#define MENU_HPP

#include <string>

class Menu {
    public:
        Menu()=default;

        // ask and check for valid input
        int askInput(int max_input);
        // clear current window
        void clear(int i);
    protected:
        bool is_number(const std::string &s);
};

#endif