#ifndef COMMON_HPP
#define COMMON_HPP

#include <string>
#include <vector>


int const IPINVALID = -3;   //client a saisi un IP invalide
int const FAILEDCONNECT= -2;//client n'a pas pu se connecter au serveur
int const FAILEDREQUEST = -1;

int const VALIDREQUEST = 0;
int const CREATIONACCOUNT = 1;  // focntionne 
int const CONNECTION = 2;       // focntionne
int const WAITINGBATTLE = 3;    // req (string): 2 ou 4 -> le nombre de joueur | reponse: req (string) <keyPlayer1>,<keyPlayer2>(,<keyPlayer3>,<keyPlayer4>)
int const MOVE = 4;             // req (string), envoie le string ecrit par le joueur, pouis renvoie la meme requete aux autre joeurs
int const GETPSEUDO = 5;    // req (string): <key_to_search>
int const GETFRIENDSLIST = 6;
int const ADDFRIEND = 7;    // req (string): <pseudo> -> rep: typeReq: 0 ou 1
int const GAMEFINISH = 8;   // depuis le client: req (string) <1 ou 0> ou 1 est gagné et 0 est perdu
                            // le server ne renvoie pasd de reponse mais actualise la db + clear le vecteur d'oposant du client lenvoyant
int const GETRANKING = 9;   // TODO
int const DISCONNECTACCOUNT = 10;   // fonctionne
int const CANCELMATCHMAKING = 11;   // TODO a faire
int const STOPCURRENTGAME = 12;     // arrete une partie en cours



struct packet {
    int typeRequest;
    std::string request;
    packet(int typeRequest, std::string request): typeRequest{typeRequest}, request{request} {};
    packet(int typeRequest): typeRequest{typeRequest}, request{""} {};
    packet()=default;
};


class Parser{
    std::vector<std::string> vectorWords;
    public:
        // Parser(string msg): vectorWords{splitBySpace(msg)} {};
        Parser(std::string msg, std::string separator): vectorWords{splitBySeparator(msg, separator)} {};
        std::vector<std::string> &getVectorWords() {return vectorWords;}
    
    private:
        std::vector<std::string> splitBySeparator(std::string line, std::string separator);
};

class FriendsParser: public Parser {
    public:
        FriendsParser(std::string s): Parser{s, "/"} {};
        std::vector<int> getFriendsKeyList();
};

class CSVParser: public Parser {
    public:
        CSVParser(std::string line): Parser{line, ","} {};

};

class ConnectionParser : public Parser{
    public:
        ConnectionParser(std::string request): Parser{request, " "} {};
        // int getKey();
        std::string getPseudo() {return Parser::getVectorWords()[0];};    // pseudo = ConnexionParser::getPseudo(msg)
        std::string getPassword() {return Parser::getVectorWords()[1];};
};

#endif
