#ifndef MATCHMAKING_HPP
#define MATCHMAKING_HPP

#include <vector>
#include <memory>
#include "client_user.hpp"


class Matchmaking {
    std::vector<std::shared_ptr<ClientUser>> waitingList2Player;
    std::vector<std::shared_ptr<ClientUser>> waitingList4Player;
    public:
        Matchmaking()=default;
        void addPlayer(int nbPlayer, std::shared_ptr<ClientUser> newClient);
        // if 2 player are ready to start a game, it will send them response with the key of the opposit player
        void updateAll();

        // TODO optimiser les 2 methodes upadte

        // Si creation de partie possible envoie la ou les clé de ses opposants a l'utilisateur
        void update2Player();
        void update4Player();
        // pour creer notre packet reponse
        std::string vectToString(std::vector<std::shared_ptr<ClientUser>> game);
        // remove an userId from the matchmaking
        void removeFromQueue(int key);
};


#endif