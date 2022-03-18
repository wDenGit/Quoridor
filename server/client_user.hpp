#ifndef CLIENT_USER_HPP
#define CLIENT_USER_HPP

#include <vector>
#include <memory>

class ClientUser {
    const int sock;
    int key;
    std::vector<std::shared_ptr<ClientUser>> inGameWith;
    public:
        ClientUser(int sock): sock{sock}, key{-1} {};

        // GETTER
        int getSocket() const {return this->sock;}
        int getKey() const {return this->key;}
        const std::vector<std::shared_ptr<ClientUser>> &getOtherPlayer() const {return this->inGameWith;}
        // SETTER
        void setKey(int key) {this->key = key;};
        void setInGameWith(std::vector<std::shared_ptr<ClientUser>> v);
        // Other Methods
        bool isInGame() {return this->inGameWith.size() > 0;}
        // Lorsqu'un utilisateur a finis sa partie on doit clear inGameWith
        void clearCurrentOppents() {this->inGameWith.clear();}
};

#endif