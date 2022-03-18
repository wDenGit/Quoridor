#include "menu.hpp"
#include <iostream>
#include <unistd.h>     // sleep()
#include <algorithm>    // all_of

using namespace std;

int Menu::askInput(int max_input) {
    string input;
    while (true) {
        cout << "Que voulez-vous faire ? : ";
        ws(cin);    // skip whitespace line, arrive a couse d'un appel cin
        getline(cin, input);
        if (this->is_number(input) && (1 <= stoi(input) && stoi(input) <=max_input))
            break;
        cout << "Input incorrect" << endl;
    }
    return stoi(input);
}

bool Menu::is_number(const std::string &s) {
    // Credit: stackoverflow
    return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}

void Menu::clear(int i) {
    sleep(i);
    cout << "\x1B[2J\x1B[H";  
}