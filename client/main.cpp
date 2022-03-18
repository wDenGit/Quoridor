#include "client.hpp"
#include <iostream>
#include <string>

#include <unistd.h>

using namespace std;

int main(int argc, char const *argv[]) {
    // check que l'on a 1 ou pas d'argument
    if (argc > 2) {
        cerr << "Wrong arguments: ./client.out <server_ip> " << endl;
        cerr << "or: " << endl;
        cerr << "If server is host on localhost: ./client.out " << endl;
        exit(EXIT_FAILURE);
    }
    string ip;
    if (argc == 2) 
        ip = argv[1];
    else    
        ip = "127.0.0.1";
    Client c;
    c.run(8080, ip);
    return 0;
}