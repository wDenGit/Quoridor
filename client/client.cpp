#include "client.hpp"
#include "menu_connection.hpp"
#include "common/common.hpp"

#include <sys/socket.h> // socket()
#include <netinet/in.h> // sockaddr_in
#include <arpa/inet.h>  // inet_pton()


using namespace std;

/**
 * Private Methods
 **/

int Client::initConnection(std::string ip, int port) {
    this->client_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Conversion de string vers IPv4 ou IPv6 en binaire
    if (inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr) == 0) {
        perror("IP adress not valid.");
        return(IPINVALID);
    }

    // on essaie de se connecter
    if (connect(this->client_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) {
        perror("connect to server failed");
        return(FAILEDCONNECT);
    }
    return 0;
}

/**
 * Public Methods
 **/

int Client::run(int port, string ip){
    int connexion_error = this->initConnection(ip, port);
    if(connexion_error<0){
        return connexion_error;
    }
    return 0;
};

int Client::getClient_socket(){
    return this->client_socket;
};
