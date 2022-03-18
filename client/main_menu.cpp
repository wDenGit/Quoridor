#include "main_menu.hpp"
#include "friendslist_menu.hpp"
#include "../common/socketlib.hpp"
#include "game_menu.hpp"

#include <iostream>
#include <unistd.h>     // sleep();

using namespace std;

void MainMenu::run() {
    int input = -1;
    while(input != options::disconnect){
        this->displayMenu();
        input = this->askInput(options::max_input);
        switch(input){
            case options::playGame: { // Se met en file d'attente, pour lancer une partie
                GameMenu gameMenu{this->sock, this->account};
                gameMenu.run();
                break;
            }
            case options::resumeGame:
                clear(0);
                cout << "\n--- Bientot disponible ---" << endl;    
                sleep(2);      
                break;

            case options::seeFriends :{    // afficher liste d'amis
                FriendsListMenu friendsListMenu{this->sock};
                friendsListMenu.run();
                break;
            }
            case options::seeRanking: // Classment
                clear(0);
                cout<<"Bientôt disponible"<<endl;       
                sleep(2);      
                break;
        }
    }
    // on dit au serveur que notre user se deconnecte de son compte
    packet p{DISCONNECTACCOUNT};
    send_packet(this->sock, &p);
    cout << "Vous etes deconnecté" << endl;
    sleep(2);
}

void MainMenu::displayMenu() {
    this->clear(0);
    cout<<"1.Commencer une partie"<<endl;
    cout<<"2.Charger une partie"<<endl;
    cout<<"3.Liste d'amis"<<endl;
    cout<<"4.Classement"<<endl;
    cout<<"5.Disconnection"<<endl;
}
