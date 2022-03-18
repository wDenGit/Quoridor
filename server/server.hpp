#ifndef SERVER_HPP
#define SERVER_HPP

#include <string.h>
#include <vector>
#include <sys/select.h>     // fd_set
#include <memory>           // shared_ptr

#include "../common/socketlib.hpp"    // packet
#include "matchmaking.hpp"
#include "client_user.hpp"

#define NB_CLIENTS_MAX  10



/*******************************
 *                             *
 *   DBManager (fichier csv)   *
 *                             *
 *******************************/


// Db = fichier texte
class DBManager {
    std::string path;
    int max_key;
    public:
        enum col{key, pseudo, password, win, loose, friendsKey, friendsRequest};
        DBManager(std::string path): path{path} {this->updateMaxKey();};
        void setPath(std::string path) {this->path=path;}
        bool addAccount(std::string pseudo, std::string mdp);
        std::vector<std::string> getAccountFromPseudo(std::string pseudo);
        std::vector<std::string> getAccountFromKey(int key);
        void addWin(int key);
        void addLoose(int key);
        bool addFriends(int userKey, int friendKey);
        std::string getPseudo(int key);

        // return string form: <key1>/<key2>/<key3>
        std::string getFriendsList(int key);

    private:
        void changeLineWithKey(int key, std::string newLine);
        std::string vectToString(std::vector<std::string> v);
        void updateMaxKey();
};


/**
 * Classe inspiré de la correction du projet d'OS
 **/
class Server {
    int master_socket;
    int max_fd;
    std::vector<std::shared_ptr<ClientUser>> clients;
    DBManager db_manager;
    Matchmaking matchmaking;
    
    public:
        Server(std::string path_csv_db="databaseaccount.csv"): db_manager{path_csv_db} {};
        void Run(int port=8080);
        void prepareFDSet(fd_set *read_set);

        void handleSocketActivity(fd_set* read_set, int& nactivities);

        void addNewSocketConnection();

        void disconnectUser(int userNum);

        void handleRequest(std::shared_ptr<ClientUser> reqSender, packet p_client);


        // Methods user for response to requests
        // return la clé du compte si connexion est reussi, sinon renvoie -1
        int connection(std::string pseudo, std::string mdp);
        bool createAccount(std::string pseudo, std::string mdp);
        bool addFriend(int userKey, std::string friendPseudo);
        bool isConnected(int key);
        void cancelCurrentGame(std::shared_ptr<ClientUser> user);
};


#endif