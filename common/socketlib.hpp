#ifndef SOCKETLIB_HPP
#define SOCKETLIB_HPP
#include <string.h>

#include "common.hpp"

/**
 * Fonctions inspiré de la correction du projet d'OS
 **/

int _checked(int ret, std::string calling_function);

#define checked(call) _checked(call, #call)

int createSocket();

void init_address(struct sockaddr_in* address, const char* ip_address, int port);

void bind_socket(int sock, int port);

void listen_socket(int socket, int max_connextion);

int send_packet(int sock, packet* message);

size_t receive_packet(int sock, packet* dest);

#endif  //SOCKETLIB_HPP