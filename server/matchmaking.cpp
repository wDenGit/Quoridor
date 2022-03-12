#include "matchmaking.hpp"
#include "../common/socketlib.hpp"

#include <iostream> // DEBUG

using namespace std;


/*******************************
 *                             *
 *        Matchmaking          *
 *                             *
 *******************************/

void Matchmaking::addPlayer(int nbPLayer, shared_ptr<ClientUser> newClient) {
    if (nbPLayer == 2) 
        this->waitingList2Player.push_back(newClient);
    else if (nbPLayer == 4)
        this->waitingList4Player.push_back(newClient);
    else
        cout << "Matchmaking::addPlayer error" << endl;
}

void Matchmaking::updateAll() {
    this->update2Player();
    this->update4Player();
}

void Matchmaking::update2Player() {
    // si moins de 2 joueurs, impossible de "creer une partie"
    if (this->waitingList2Player.size() < 2) return;

    shared_ptr<ClientUser> player1, player2;
    player1 = waitingList2Player.at(0);
    player2 = waitingList2Player.at(1);
    this->waitingList2Player.erase(this->waitingList2Player.begin(), this->waitingList2Player.begin()+2);  // supprime les 2 elements de notre liste

    // on creer notre vecteur jeu que l'on va set a chaque joueur
    vector<shared_ptr<ClientUser>> game = vector<shared_ptr<ClientUser>>();
    game.push_back(player1);
    game.push_back(player2);
    player1->setInGameWith(game);
    player2->setInGameWith(game);

    // on creer le packet
    packet p{VALIDREQUEST, this->vectToString(game)};

    // on l'envoie a nos 2 joueurs
    send_packet(player1->getSocket(), &p);
    send_packet(player2->getSocket(), &p);
}

void Matchmaking::update4Player() {
    // si moins de 4 joueurs, impossible de "creer une partie"
    if (this->waitingList4Player.size() < 4) return;

    shared_ptr<ClientUser> player1, player2, player3, player4;
    player1 = waitingList4Player[0];
    player2 = waitingList4Player[1];
    player3 = waitingList4Player[2];
    player4 = waitingList4Player[3];
    waitingList4Player.erase(waitingList4Player.begin(), waitingList4Player.begin()+4);  // supprime les 2 elements de notre liste

    // on creer notre vecteur jeu que l'on va set a chaque joueur
    vector<shared_ptr<ClientUser>>  game = vector<shared_ptr<ClientUser>>();
    game.push_back(player1);
    game.push_back(player2);
    game.push_back(player3);
    game.push_back(player4);
    player1->setInGameWith(game);
    player2->setInGameWith(game);
    player3->setInGameWith(game);
    player4->setInGameWith(game);

    // on creer le packet
    packet p{VALIDREQUEST, this->vectToString(game)};

    // on l'envoie a nos 2 joueurs
    send_packet(player1->getSocket(), &p);
    send_packet(player2->getSocket(), &p);
    send_packet(player3->getSocket(), &p);
    send_packet(player4->getSocket(), &p);
}

string Matchmaking::vectToString(vector<shared_ptr<ClientUser>> v) {
    string toReturn;
    for (auto &i: v)
        toReturn.append(to_string(i->getKey())+"/");
    // toReturn.erase(toReturn.end()-1);    // car on utilise le FirendsParser qui a besoin du dernier '/'
    return toReturn;
}

void Matchmaking::removeFromQueue(int key) {
    // verifie d'abord dans la queue 1vs1
    for (size_t i=0; i<this->waitingList2Player.size(); i++) {
        if (this->waitingList2Player[i]->getKey() == key) { // si notre clé est dans la liste on la supprime
            this->waitingList2Player.erase(this->waitingList2Player.begin()+i);
            return;
        }
    }
    // verifie ensuite dans la queue 2vs2
    for (size_t i=0; i<this->waitingList4Player.size(); i++) {
        if (this->waitingList4Player[i]->getKey() == key) { // si notre clé est dans la liste on la supprime
            this->waitingList4Player.erase(this->waitingList4Player.begin()+i);
            return;
        }
    }
}