#include <iostream>
#include <sys/select.h> // fd_set
#include <sys/socket.h> // socket()
#include <netinet/in.h> // sockaddr_in
#include <unistd.h>     // write() / read()

#include "socketlib.hpp"

using namespace std;

int _checked(int ret, std::string calling_function) {
    if (ret < 0) {
        perror(calling_function.c_str());
        exit(EXIT_FAILURE);
    }
    return ret;
};


int createSocket() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == 0){
        perror("Socket Failed");
        exit(EXIT_FAILURE);
    }

    const int opt = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *) &opt, sizeof(opt))) {
        perror("setsocketopt failed");
        exit(EXIT_FAILURE);
    }

    return fd;
};

void init_address(struct sockaddr_in* address, const char* ip_address, int port) {  // TODO ip_address not use in init_address
    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(port);
};

void bind_socket(int sock, int port){
    struct sockaddr_in address;
    init_address(&address, "", port);

    if (bind(sock, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
};

void listen_socket(int socket, int max_connextion) {
    if (listen(socket, max_connextion) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
};

int send_packet(int sock, packet* message) {
    size_t len = message->request.length();
    checked(write(sock, &len, sizeof(len)));
    checked(write(sock, &message->typeRequest, sizeof(message->typeRequest)));
    checked(write(sock, message->request.c_str(), len));
    // std::cout << "send_packet: len="<<len<<", typeRequest="<<message->typeRequest<<", request="<<message->request<<std::endl;
    return len;
};

size_t receive_packet(int sock, packet* dest) {
    size_t nbytes_to_receive;
    // Receive Size
    if (checked(read(sock, &nbytes_to_receive, sizeof(nbytes_to_receive))) == 0) {
        // Connection closed
        return 0;
    }
    char buffer[nbytes_to_receive];
    if (buffer == NULL) {
        fprintf(stderr, "malloc could not allocate %zd bytes", nbytes_to_receive);
        perror("");
        exit(1);
    }
    // Receive typeRequest
    checked(read(sock, &dest->typeRequest, sizeof(dest->typeRequest)));
    // Receive Message
    size_t received = checked(read(sock, &buffer, nbytes_to_receive));
    buffer[nbytes_to_receive] = '\0';
    dest->request = std::string(buffer);
    // std::cout << "Reçu : " << dest->request << std::endl;
    return received+sizeof(size_t);
};
