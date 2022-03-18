#include "game_menu.hpp"
#include "../common/socketlib.hpp"
#include "game.hpp"
#include <iostream>
#include <unistd.h> // sleep()

using namespace std;

void GameMenu::run() {
    int input = -1;
    while (input != options::exit) {
        this->displayPlayGameMenu();
        input = this->askInput(options::max_input);
        switch (input) {
            case options::randomMatchmaking2players: {
                // dis au serveur qu'on veut jouer à 2
                packet p{WAITINGBATTLE, "2"};
                send_packet(this->sock, &p);
                cout << "J'attends un adversaire." << endl;
                receive_packet(this->sock, &p);
                if (p.typeRequest == FAILEDREQUEST) {
                    cout << "Matchmaking échoué." << endl;
                    sleep(2);
                    break;
                }
                if (p.typeRequest == VALIDREQUEST) {
                    this->startGame(p.request);
                    break;
                }
            }
            case options::randomMatchmaking4players: {
                packet p{WAITINGBATTLE, "4"};
                send_packet(this->sock, &p);
                cout << "J'attends des adversaires." << endl;
                receive_packet(this->sock, &p);
                if (p.typeRequest == FAILEDREQUEST) {
                    cout << "Matchmaking échoué." << endl;
                    sleep(2);
                    break;
                }
                if (p.typeRequest == VALIDREQUEST) {
                    this->startGame(p.request);
                    break;
                }
            }
        }
    }
}


/**
 * Private Methods
 */

void GameMenu::displayPlayGameMenu() {
    this->clear(0);
    cout << "1.Jouer en 1vs1" << endl;
    cout << "2.Jouer en 2vs2" << endl;
    cout << "3.Retour" << endl;
}

void GameMenu::startGame(std::string serverRequest) {
    this->clear(0);
    FriendsParser parser{serverRequest};
    vector<int> keysOtherPlayers = parser.getFriendsKeyList();
    Game game{this->sock, this->myKey, keysOtherPlayers};
    game.playGame();
}