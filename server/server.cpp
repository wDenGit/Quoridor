#include <sys/socket.h> // socket()
#include <fstream>
#include <iostream>
#include <algorithm> // find()
#include <assert.h>

#include "server.hpp"

using namespace std;

/*******************************
 *                             *
 *          DBManager          *
 *                             *
 *******************************/

/********************
 * Privates Methods *
 ********************/

void DBManager::changeLineWithKey(int key, string newLine) {
    // on doit récrire tout le fichier pour le modifié
    vector<string> tmp; // use as temp memory of the file, for rewrite it with the modification
    ifstream db_file;

    db_file.open(this->path);

    // on creer un vecteur de string qu'on utilisera pour réecrire le ficher
    string line;
    while(getline(db_file, line)) {
        CSVParser parser{line};
        if (stoi(parser.getVectorWords()[col::key]) == key) {
            tmp.push_back(newLine);
        }
        else
            tmp.push_back(line);
    }
    db_file.close();

    // erased the old file with the string from tmps 
    ofstream newFile;
    newFile.open(this->path);
    for (auto &s: tmp)
        newFile << s << "\n";
    newFile.close();
}

string DBManager::vectToString(vector<string> v) {
    string toReturn;
    for (string &s: v)
        toReturn.append(s + ",");
    // suprrime la derniere virgule
    toReturn.erase(toReturn.end()-1);
    return toReturn;
}

void DBManager::updateMaxKey() {
    this->max_key = 0;
    string line;
    ifstream db_file{this->path};
    // ifstream db_file;
    // db_file.open(this->)

    while(getline(db_file, line))
        this->max_key++;
    
}

/*******************
 * Publics Methods *
 *******************/

bool DBManager::addAccount(string pseudo, string mdp) {
    ifstream db_file(this->path);
    string line;
    int count = 0;
    // verifie que le pseudo ne soit pas deja utilisé
    while(getline(db_file, line)) {
        count++;
        CSVParser parser(line);
        if (parser.getVectorWords()[col::pseudo] == pseudo) {
            return false;
        }
    }
    
    // le pseudo n'est pas deja utilisé, donc on l'ajoute
    ofstream db_fileW(this->path, ios::out | ios::app);
    db_fileW.seekp(0, ios_base::end);
    db_fileW << count + 1 << "," << pseudo << "," << mdp << ",0,0,,"<< endl;
    // update max_key
    this->max_key = count + 1;
    return true;
}

vector<string> DBManager::getAccountFromPseudo(string pseudo) {
    ifstream db_file(this->path);
    string line;
    // cherche le bon pseudo
    while(getline(db_file, line)) {
        CSVParser parser(line);
        if (parser.getVectorWords()[this->col::pseudo] == pseudo) {
            return parser.getVectorWords();
        }
    }
    perror("Pas de compte a la clé 'key'");
    // sinon on return un vecteur vide
    return vector<string>{};
}

vector<string> DBManager::getAccountFromKey(int key) {
    ifstream db_file(this->path);
    string line;
    // cherche le bon pseudo
    while(getline(db_file, line)) {
        CSVParser parser(line);
        if (stoi(parser.getVectorWords()[this->col::key]) == key) {
            return parser.getVectorWords();
        }
    }
    // sinon on return un vecteur vide
    perror("Pas de compte a la clé 'key'");
    return vector<string>{};
}

void DBManager::addWin(int key) {
    vector<string> accountData = this->getAccountFromKey(key);
    accountData.at(col::win) = to_string(stoi(accountData.at(col::win)) + 1);
    this->changeLineWithKey(key, vectToString(accountData));
}

void DBManager::addLoose(int key) {
    vector<string> accountData = this->getAccountFromKey(key);
    accountData.at(col::loose) = to_string(stoi(accountData.at(col::loose)) + 1);
    this->changeLineWithKey(key, vectToString(accountData));
}

bool DBManager::addFriends(int userKey, int friendKey) {
    // si clé n'existe pas -> erreur
    if (friendKey > this->max_key)  return false;
    // si on veut s'ajouter soit meme en ami -> erreur
    if (userKey == friendKey) return false;

    vector<string> accountData = this->getAccountFromKey(userKey);
    // verifie que l'ami ne soit pas deja dans la liste
    FriendsParser parser{accountData[col::friendsKey]};
    vector<int> keys = parser.getFriendsKeyList();
    if (find(keys.begin(), keys.end(), friendKey) != keys.end())    // ils sont deja amis
        return false;
    
    // comme ils ne sont pas amis, on l'ajoute
    accountData.at(col::friendsKey) = accountData.at(col::friendsKey) + to_string(friendKey) + "/";
    this->changeLineWithKey(userKey, vectToString(accountData));
    return true;
}

string DBManager::getPseudo(int key) {
    return this->getAccountFromKey(key)[col::pseudo];
}

string DBManager::getFriendsList(int key) {
    return this->getAccountFromKey(key)[col::friendsKey];
}



/*******************************
 *                             *
 *          Server             *
 *                             *
 *******************************/

void Server::Run(int port) { 
    // Configuration du master socket
    this->master_socket = createSocket();
    bind_socket(this->master_socket, port);
    listen_socket(master_socket, NB_CLIENTS_MAX);
    cout << "Server running on port " << port << endl;

    this->max_fd = master_socket; 

    fd_set readfds;
    while (true){
        // Boucle server
        this->prepareFDSet(&readfds);

        // select wait for an activity
        int nactivites = checked(select(max_fd + 1 , &readfds , NULL , NULL , NULL));

        this->handleSocketActivity(&readfds, nactivites);
    }
}
 

void Server::prepareFDSet(fd_set *read_set) {
    FD_ZERO(read_set);
    FD_SET(this->master_socket, read_set);
    int nb_clients = clients.size();
    for (int i=0; i<nb_clients; i++) {
        shared_ptr<ClientUser> user = clients[i];
        FD_SET(user->getSocket(), read_set);
        this->max_fd = (user->getSocket() > max_fd) ? user->getSocket() : max_fd;
    }
}


void Server::handleSocketActivity(fd_set* read_set, int& nactivities) {
    if (nactivities <= 0) return;
    // si c'est le master socker qui a des données, c'est une nouvelle connection
    if (FD_ISSET(this->master_socket, read_set)) {
        this->addNewSocketConnection();
        nactivities--;
    }

    int nb_clients = this->clients.size() - 1;
    while (nactivities > 0 && nb_clients >= 0) {
        int sock = this->clients[nb_clients]->getSocket();

        // si le message vient de ce client
        if (FD_ISSET(sock, read_set)) {
            nactivities--;

            packet p_client;
            int bytes_received = receive_packet(sock, &p_client);
            if (bytes_received > 0) {
                this->handleRequest(this->clients[nb_clients], p_client);
            }
            else if (bytes_received == 0) 
                this->disconnectUser(nb_clients);
            else{ // si bytes_received < 0 -> server a crash 
                perror("je sais pas mais dans Server::handleSocketActivity()");
                exit(EXIT_FAILURE);
            }
        }
        nb_clients--;
    }
}


void Server::addNewSocketConnection() {
    struct sockaddr remote_host;
    unsigned addr_len = sizeof(&remote_host);

    shared_ptr<ClientUser> newClient = make_shared<ClientUser>(accept(master_socket, &remote_host, &addr_len));

    cout << "New connection - socket fd : " << newClient->getSocket() << endl;
    clients.push_back(newClient);
    // actualise le max_fd
    this->max_fd = (newClient->getSocket() > this->max_fd) ? newClient->getSocket() : this->max_fd;
}

void Server::disconnectUser(int userNum) {
    shared_ptr<ClientUser> user = this->clients[userNum];
    this->clients.erase(clients.begin() + userNum);
    // supprime notre objet client dans matchmaking
    this->matchmaking.removeFromQueue(user->getKey());
    if (user->isInGame()) {
        this->cancelCurrentGame(user);
    }
    assert(user.use_count() == 1);  // si ce n'est pas le cas, un de nos pointeur client dois etre supprimer qql part
    // reinitialise le max_fd
    this->max_fd = this->master_socket;
    for (auto user: this->clients) {
        if (user->getSocket() > this->max_fd)
            this->max_fd = user->getSocket();
    }
    cout << "Client déconnecté de clé: " << user->getKey() << ", et de socket: " << user->getSocket() << endl;
}


void Server::handleRequest(shared_ptr<ClientUser> reqSender, packet p_client) {
    cout << "Requete recu de socket: " << reqSender->getSocket() << ", de clé: " << reqSender->getKey() << ", de type: ";
    switch(p_client.typeRequest) {
        case CREATIONACCOUNT: {
            cout << "CREATIONACCOUNT" << endl;
            ConnectionParser parser{p_client.request};
            // renvoie 0 si creation reussi, snn -1 au client
            if (this->createAccount(parser.getPseudo(), parser.getPassword()))
                p_client.request = to_string(VALIDREQUEST);
            else
                p_client.request = to_string(FAILEDREQUEST);
            send_packet(reqSender->getSocket(), &p_client);
            break;
        }
        case CONNECTION: {
            cout << "CONNECTION" << endl;
            ConnectionParser parser{p_client.request};
            int userKey = this->connection(parser.getPseudo(), parser.getPassword());
            reqSender->setKey(userKey);
            p_client.request = to_string(userKey);
            send_packet(reqSender->getSocket(), &p_client);
            break;
        }
        case WAITINGBATTLE: {
            cout << "WAITINGBATTLE" << endl;
            int nbJoueur = stoi(p_client.request);
            if (nbJoueur == 2)
                this->matchmaking.addPlayer(2, reqSender);
            else if (nbJoueur == 4)
                this->matchmaking.addPlayer(4, reqSender);
            else
                cout << "erreur Requete WAITINBATTLE" << endl;
            this->matchmaking.updateAll();
            break;
        }
        case MOVE:{
            cout << "MOVE" << endl;
            // on fait que renvoie le coup recu aux autre joeuurs
            for (auto &otherPlayer: reqSender->getOtherPlayer())
                send_packet(otherPlayer->getSocket(), &p_client);
            break;
        }
        case GETPSEUDO: {
            cout << "GETPSEUDO" << endl;
            int keyToSearch = stoi(p_client.request);
            packet p_response{VALIDREQUEST, this->db_manager.getPseudo(keyToSearch)};
            send_packet(reqSender->getSocket(), &p_response);
            break;
        }
        case GETFRIENDSLIST: {
            cout << "GETFRIENDSLISTS" << endl;
            packet p_response{VALIDREQUEST, this->db_manager.getFriendsList(reqSender->getKey())};
            send_packet(reqSender->getSocket(), &p_response);
            break;
        }
        case ADDFRIEND: {
            cout << "ADDFRIENDS" << endl;
            packet p_response;
            p_response.request = "";
            if (this->addFriend(reqSender->getKey(), p_client.request))
                p_response.typeRequest = VALIDREQUEST;
            else
                p_response.typeRequest = FAILEDREQUEST;
            send_packet(reqSender->getSocket(), &p_response);
            break;
        }
        case GAMEFINISH: { 
            cout << "GAMEFINISH" << endl;
            if (stoi(p_client.request) == 1)    // notre client a gagné
                this->db_manager.addWin(reqSender->getKey());
            else
                this->db_manager.addLoose(reqSender->getKey());
            // on actualise son status
            reqSender->clearCurrentOppents();
            break;
        }
        case GETRANKING: {
            cout << "GETRANKING" << endl;
            // TODO
            break;
        }
        case DISCONNECTACCOUNT: {
            cout << "DISCONNECTACCOUNT" << endl;
            reqSender->setKey(-1);  // car n'est plus connecté
            break;
        }
        case STOPCURRENTGAME: {
            cout << "STOP CURRENTGAME" << endl;
            this->cancelCurrentGame(reqSender);
            break;
        }
        default:
            cout << "Requête inconnue \n";
            break;
    }
}

int Server::connection(string pseudo, string mdp) {
    // get les infos de notre pseudo
    vector<string> acc = this->db_manager.getAccountFromPseudo(pseudo);
    
    // si pseudo n'existe pas
    if (acc.size() == 0) return -1;

    // verifie que notre user n'est pas deja connecté
    if (this->isConnected(stoi(acc[DBManager::key]))) return -1;

    if (acc[DBManager::password] == mdp) {
        // cout << "c'est le meme mdp donc on renvoit la clé: " << acc[DBManager::key] << endl;
        return stoi(acc[DBManager::key]);
    }
    else{
        // cout << "Mauvais password" << endl;
        return -1;
    }
}

bool Server::createAccount(string pseudo, string mdp) {
    return this->db_manager.addAccount(pseudo, mdp);
}

void Server::cancelCurrentGame(shared_ptr<ClientUser> user) {
    assert(user->isInGame());
    // on envoie aux autre joueurs le fait que la partie s'arrete + clear les oppposant des autres joueurs
    packet p{STOPCURRENTGAME};
    for (auto &otherPlayer: user->getOtherPlayer()) {
        send_packet(otherPlayer->getSocket(), &p);
        otherPlayer->clearCurrentOppents();
    }
    // maintenant on clear mes opposants à moi
    user->clearCurrentOppents();
}

bool Server::isConnected(int key) {
    for (auto &user: this->clients) {
        if (key == user->getKey())
            return true;
    }
    return false;
}

bool Server::addFriend(int userKey, string friendPseudo) {
    vector<string> acc = this->db_manager.getAccountFromPseudo(friendPseudo);
    // si pseudo n'existe pas
    if (acc.size() == 0) {return false;}

    // si ami existe, on essaie de l'ajouté
    return this->db_manager.addFriends(userKey, stoi(acc[DBManager::col::key]));
}
