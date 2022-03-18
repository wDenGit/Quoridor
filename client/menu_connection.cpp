#include "menu_connection.hpp"
#include "../common/socketlib.hpp"

using namespace std;

int MenuConnection::createAccount(int client_socket, std::string pseudo, std::string mdp) {
    packet p{CREATIONACCOUNT, pseudo + " " + mdp};
    send_packet(client_socket, &p);
    // attend reponse
    receive_packet(client_socket, &p);
    return stoi(p.request);
}

int MenuConnection::connection(int client_socket, std::string pseudo, std::string mdp) {
    packet p{CONNECTION, pseudo + " " + mdp};
    send_packet(client_socket, &p);
    // attend reponse
    receive_packet(client_socket, &p);
    return stoi(p.request);
}
