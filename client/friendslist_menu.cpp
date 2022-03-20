#include "friendslist_menu.hpp"
#include "../common/socketlib.hpp"
#include <iostream>
#include <unistd.h> // sleep()
#include <algorithm> // all_of

using namespace std;

void FriendsListMenu::updateAll() {
    this->friendsKey.clear();
    this->friendsPseudo.clear();
    packet p{GETFRIENDSLIST};
    send_packet(this->sock, &p);
    // attends notre reponse
    receive_packet(this->sock, &p);
    FriendsParser parser{p.request};
    this->friendsKey = parser.getFriendsKeyList();
    this->updatePseudo();
}

void FriendsListMenu::updatePseudo() {
    for (int &i: this->friendsKey) {
        packet p_pseudo{GETPSEUDO, to_string(i)};
        send_packet(this->sock, &p_pseudo);
        receive_packet(this->sock, &p_pseudo);
        this->friendsPseudo.push_back(p_pseudo.request);
    }
}

void FriendsListMenu::run() {
    int user_choice = -1;
    while(user_choice != options::exit) {
        this->displayFriends();
        this->displayOptions();
        user_choice = this->askInput(options::max_input);

        switch (user_choice){
            case options::addFriendChoice: {
                clear(0);
                string pseudo;
                cout << "Ajout d'amis" << endl << "Entrez le pseudo de votre ami: ";
                cin >> pseudo;
                cout << endl;
                if (this->addFriend(pseudo)) {
                    cout << "Ajout reussi" << endl;
                    this->updateAll();
                }
                else
                    cout << "Ajout de l'ami a échoué" << endl;
                sleep(2);
                break;
            }
        }
    }
}

void FriendsListMenu::displayFriends() {
    this->clear(0);
    cout << "Vos Amis: " << endl;
    int count = 1;
    for (string &pseudo: this->friendsPseudo) {
        cout << count << ") " << pseudo << endl;
        count++;
    }
    cout << endl;
}

vector<string> FriendsListMenu::displayFriendsQT(){ // Seulement pour afficher dans le UI
    return friendsPseudo;
}

void FriendsListMenu::displayOptions() {
    cout << "1.Ajouter un ami" << endl;
    cout << "2.Retourner au menu" << endl;
}

bool FriendsListMenu::addFriend(string pseudo) {
    packet p{ADDFRIEND, pseudo};
    send_packet(this->sock, &p);
    receive_packet(this->sock, &p);
    if (p.typeRequest == 0)
        return true;
    else
        return false;
}
