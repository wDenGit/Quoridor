#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client {
    int	client_socket;

    public:
        Client()=default;
        int run(int port, std::string ip);
        int getClient_socket();

    private:
        int initConnection(std::string ip, int port);
};

#endif
